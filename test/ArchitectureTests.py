"""Regression fixtures reject invalid public-header paths and domain dependency edges."""

import argparse
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

from CheckArchitecture import ArchitectureError, check


SOURCE_ROOT = Path(__file__).resolve().parents[1]
CMAKE = "cmake"
HEADER_FOR_DOMAIN = {
    "Equipment": "Type.h",
    "Error": "Result.h",
    "Factions": "Id.h",
    "Observations": "Id.h",
    "Orders": "IProvider.h",
    "Operations": "Activity.h",
    "Physics": "Position.h",
    "Resources": "Id.h",
    "Units": "Id.h",
    "Uncertainty": "Exact.h",
}


class ArchitectureTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix="domain-architecture-")
        self.root = Path(self.temporary.name)
        shutil.copytree(SOURCE_ROOT / "public", self.root / "public")

    def tearDown(self):
        self.temporary.cleanup()

    def configure(self, additional_cmake=""):
        source_targets = (SOURCE_ROOT / "src" / "CMakeLists.txt").as_posix()
        exporter = (SOURCE_ROOT / "test" / "ExportDomainGraph.cmake").as_posix()
        project = (
            "cmake_minimum_required(VERSION 4.2)\n"
            "project(ArchitectureFixture LANGUAGES NONE)\n"
            "function(NavalCommandConfigureTarget target)\nendfunction()\n"
            "function(NavalCommandConfigureDomainTarget target)\n"
            "  NavalCommandConfigureTarget(\"${target}\")\n"
            "  set_target_properties(\"${target}\" PROPERTIES CXX_STANDARD 23 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)\n"
            "  get_target_property(targetType \"${target}\" TYPE)\n"
            "  if(targetType STREQUAL \"INTERFACE_LIBRARY\")\n"
            "    set_property(TARGET \"${target}\" PROPERTY INTERFACE_COMPILE_FEATURES cxx_std_23)\n"
            "  endif()\n"
            "endfunction()\n"
            f'include("{source_targets}")\n'
            f"{additional_cmake}\n"
            f'include("{exporter}")\n'
        )
        (self.root / "CMakeLists.txt").write_text(project, encoding="utf-8")
        result = subprocess.run(
            [CMAKE, "-S", str(self.root), "-B", str(self.root / "build")],
            capture_output=True,
            text=True,
            check=False,
        )
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        return self.root / "build" / "domain-targets.txt"

    def assert_rejected(self, manifest, diagnostic):
        with self.assertRaisesRegex(ArchitectureError, diagnostic):
            check(self.root, manifest)

    def append_include(self, owner, included):
        header = self.root / "public" / "NavalCommand" / owner / "Api" / HEADER_FOR_DOMAIN[owner]
        leaf = HEADER_FOR_DOMAIN[included]
        with header.open("a", encoding="utf-8") as stream:
            stream.write(f"\n#include <NavalCommand/{included}/Api/{leaf}>\n")

    def test_current_graph(self):
        check(self.root, self.configure())

    def test_forbidden_units_orders_include(self):
        self.append_include("Units", "Orders")
        self.assert_rejected(self.configure(), r"forbidden include edge Units.Api -> Orders.Api")

    def test_forbidden_units_observations_include(self):
        self.append_include("Units", "Observations")
        self.assert_rejected(self.configure(), r"forbidden include edge Units.Api -> Observations.Api")

    def test_forbidden_units_operations_include(self):
        self.append_include("Units", "Operations")
        self.assert_rejected(self.configure(), r"forbidden include edge Units.Api -> Operations.Api")

    def test_forbidden_observations_orders_include(self):
        self.append_include("Observations", "Orders")
        self.assert_rejected(self.configure(), r"forbidden include edge Observations.Api -> Orders.Api")

    def test_forbidden_equipment_units_include(self):
        self.append_include("Equipment", "Units")
        self.assert_rejected(self.configure(), r"forbidden include edge Equipment.Api -> Units.Api")

    def test_forbidden_units_orders_target(self):
        manifest = self.configure("target_link_libraries(Units.Api INTERFACE Orders.Api)")
        self.assert_rejected(manifest, r"forbidden target edge Units.Api -> Orders.Api")

    def test_forbidden_orders_observations_target(self):
        manifest = self.configure("target_link_libraries(Orders.Api INTERFACE Observations.Api)")
        self.assert_rejected(manifest, r"forbidden target edge Orders.Api -> Observations.Api")

    def test_forbidden_units_observations_target(self):
        manifest = self.configure("target_link_libraries(Units.Api INTERFACE Observations.Api)")
        self.assert_rejected(manifest, r"forbidden target edge Units.Api -> Observations.Api")

    def test_forbidden_units_operations_target(self):
        manifest = self.configure("target_link_libraries(Units.Api INTERFACE Operations.Api)")
        self.assert_rejected(manifest, r"forbidden target edge Units.Api -> Operations.Api")

    def test_units_operations_header_cycle(self):
        self.append_include("Units", "Operations")
        self.assert_rejected(self.configure(), r"Public header cycle:")

    def test_units_operations_target_cycle(self):
        manifest = self.configure("target_link_libraries(Units.Api INTERFACE Operations.Api)")
        self.assert_rejected(manifest, r"CMake target cycle:")

    def test_operations_target_uses_cpp23(self):
        manifest = self.configure(
            "set_target_properties(Operations.Api PROPERTIES CXX_STANDARD 26 INTERFACE_COMPILE_FEATURES cxx_std_26)"
        )
        self.assert_rejected(manifest, r"target Operations.Api must use C\+\+23")

    def test_domain_target_uses_cpp23(self):
        manifest = self.configure(
            "set_target_properties(Units.Api PROPERTIES CXX_STANDARD 26 INTERFACE_COMPILE_FEATURES cxx_std_26)"
        )
        self.assert_rejected(manifest, r"target Units.Api must use C\+\+23")

    def test_evaluated_target_cycle(self):
        manifest = self.configure("target_link_libraries(Physics.Api INTERFACE Equipment.Api)")
        self.assert_rejected(manifest, r"CMake target cycle:")

    def test_header_cycle(self):
        self.append_include("Physics", "Equipment")
        self.assert_rejected(self.configure(), r"Public header cycle:")

    def test_missing_actual_direct_link(self):
        manifest = self.configure(
            'set_property(TARGET Orders.Api PROPERTY INTERFACE_LINK_LIBRARIES "Units.Api;Physics.Api")'
        )
        self.assert_rejected(manifest, r"Orders.Api direct links .* must exactly match")

    def test_external_link_rejected(self):
        manifest = self.configure(
            "add_library(External INTERFACE)\n"
            "target_link_libraries(Units.Api INTERFACE External)"
        )
        self.assert_rejected(manifest, r"unknown/external/alias/generator-expression dependency External")

    def test_alias_link_rejected(self):
        manifest = self.configure(
            "add_library(HiddenOrders ALIAS Orders.Api)\n"
            "target_link_libraries(Units.Api INTERFACE HiddenOrders)"
        )
        self.assert_rejected(manifest, r"unknown/external/alias/generator-expression dependency HiddenOrders")

    def test_generator_expression_link_rejected(self):
        manifest = self.configure('target_link_libraries(Units.Api INTERFACE "$<$<BOOL:1>:Orders.Api>")')
        self.assert_rejected(manifest, r"unknown/external/alias/generator-expression dependency")

    def test_relative_include_rejected(self):
        header = self.root / "public" / "NavalCommand" / "Units" / "Api" / "Id.h"
        with header.open("a", encoding="utf-8") as stream:
            stream.write('\n#include "../../Orders/Api/IProvider.h"\n')
        self.assert_rejected(self.configure(), r"quoted/relative public include is forbidden")

    def test_macro_include_rejected(self):
        header = self.root / "public" / "NavalCommand" / "Units" / "Api" / "Id.h"
        with header.open("a", encoding="utf-8") as stream:
            stream.write(
                "\n#define HIDDEN_ORDER_HEADER <NavalCommand/Orders/Api/IProvider.h>\n"
                "#include HIDDEN_ORDER_HEADER\n"
            )
        self.assert_rejected(self.configure(), r"macro/nonliteral public include is forbidden")

    def test_removed_domain_header_rejected(self):
        catalog = self.root / "public" / "NavalCommand" / "Catalog" / "Api"
        catalog.mkdir(parents=True)
        (catalog / "Legacy.h").write_text(
            "#pragma once\nnamespace NavalCommand::Catalog::Api {}\n",
            encoding="utf-8",
        )
        self.assert_rejected(self.configure(), r"exported header must use public/NavalCommand")

    def test_removed_domain_target_rejected(self):
        manifest = self.configure("add_library(Catalog.Api INTERFACE)")
        self.assert_rejected(manifest, r"invalid target graph record")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--cmake", default="cmake")
    arguments, unittest_arguments = parser.parse_known_args()
    CMAKE = arguments.cmake
    unittest.main(argv=[__file__] + unittest_arguments)
