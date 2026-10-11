"""Regression fixtures mutate real public headers and evaluated INTERFACE CMake target edges."""

import argparse
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

from CheckArchitecture import ArchitectureError, check


SOURCE_ROOT = Path(__file__).resolve().parents[1]
CMAKE = "cmake"


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
            # Compiler policy is irrelevant here: configure actual INTERFACE libraries without builds.
            "function(NavalCommandConfigureTarget target)\nendfunction()\n"
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
        header = next((self.root / "public" / "NavalCommand" / owner / "Api").glob("*.h"))
        header_names = {
            "Orders": "Request.h",
            "World": "ObserverSnapshot.h",
            "Observations": "UnitObservation.h",
            "Uncertainty": "Exact.h",
            "Units": "UnitInstance.h",
        }
        leaf = header_names[included]
        with header.open("a", encoding="utf-8") as stream:
            stream.write(f"\n#include <NavalCommand/{included}/Api/{leaf}>\n")

    def test_current_graph(self):
        check(self.root, self.configure())

    def test_forbidden_units_orders_include(self):
        self.append_include("Units", "Orders")
        self.assert_rejected(self.configure(), r"forbidden include edge Units.Api -> Orders.Api")

    def test_forbidden_units_world_include(self):
        self.append_include("Units", "World")
        self.assert_rejected(self.configure(), r"forbidden include edge Units.Api -> World.Api")

    def test_forbidden_world_orders_include(self):
        self.append_include("World", "Orders")
        self.assert_rejected(self.configure(), r"forbidden include edge World.Api -> Orders.Api")

    def test_forbidden_units_observations_include(self):
        self.append_include("Units", "Observations")
        self.assert_rejected(self.configure(), r"forbidden include edge Units.Api -> Observations.Api")

    def test_forbidden_units_uncertainty_include(self):
        self.append_include("Units", "Uncertainty")
        self.assert_rejected(self.configure(), r"forbidden include edge Units.Api -> Uncertainty.Api")

    def test_forbidden_observations_units_include(self):
        self.append_include("Observations", "Units")
        self.assert_rejected(self.configure(), r"forbidden include edge Observations.Api -> Units.Api")

    def test_forbidden_units_orders_target(self):
        manifest = self.configure("target_link_libraries(Units.Api INTERFACE Orders.Api)")
        self.assert_rejected(manifest, r"forbidden target edge Units.Api -> Orders.Api")

    def test_forbidden_orders_units_target(self):
        manifest = self.configure("target_link_libraries(Orders.Api INTERFACE Units.Api)")
        self.assert_rejected(manifest, r"forbidden target edge Orders.Api -> Units.Api")

    def test_forbidden_units_uncertainty_target(self):
        manifest = self.configure("target_link_libraries(Units.Api INTERFACE Uncertainty.Api)")
        self.assert_rejected(manifest, r"forbidden target edge Units.Api -> Uncertainty.Api")

    def test_forbidden_units_world_target(self):
        manifest = self.configure("target_link_libraries(Units.Api INTERFACE World.Api)")
        self.assert_rejected(manifest, r"forbidden target edge Units.Api -> World.Api")

    def test_forbidden_world_orders_target(self):
        manifest = self.configure("target_link_libraries(World.Api INTERFACE Orders.Api)")
        self.assert_rejected(manifest, r"forbidden target edge World.Api -> Orders.Api")

    def test_evaluated_target_cycle(self):
        manifest = self.configure("target_link_libraries(Physics.Api INTERFACE Catalog.Api)")
        self.assert_rejected(manifest, r"CMake target cycle:")

    def test_header_cycle(self):
        header = self.root / "public" / "NavalCommand" / "Physics" / "Api" / "Meters.h"
        with header.open("a", encoding="utf-8") as stream:
            stream.write("\n#include <NavalCommand/Catalog/Api/EquipmentType.h>\n")
        self.assert_rejected(self.configure(), r"Public header cycle:")

    def test_missing_actual_direct_link(self):
        manifest = self.configure('set_property(TARGET Orders.Api PROPERTY INTERFACE_LINK_LIBRARIES "Units.Api;Physics.Api")')
        self.assert_rejected(manifest, r"Orders.Api direct links .* must exactly match")

    def test_external_link_rejected(self):
        manifest = self.configure("add_library(External INTERFACE)\ntarget_link_libraries(Units.Api INTERFACE External)")
        self.assert_rejected(manifest, r"unknown/external/alias/generator-expression dependency External")

    def test_alias_link_rejected(self):
        manifest = self.configure("add_library(HiddenOrders ALIAS Orders.Api)\ntarget_link_libraries(Units.Api INTERFACE HiddenOrders)")
        self.assert_rejected(manifest, r"unknown/external/alias/generator-expression dependency HiddenOrders")

    def test_generator_expression_link_rejected(self):
        manifest = self.configure('target_link_libraries(Units.Api INTERFACE "$<$<BOOL:1>:Orders.Api>")')
        self.assert_rejected(manifest, r"unknown/external/alias/generator-expression dependency")

    def test_relative_include_rejected(self):
        header = self.root / "public" / "NavalCommand" / "Units" / "Api" / "UnitId.h"
        with header.open("a", encoding="utf-8") as stream:
            stream.write('\n#include "../../Orders/Api/Request.h"\n')
        self.assert_rejected(self.configure(), r"quoted/relative public include is forbidden")

    def test_macro_include_rejected(self):
        header = self.root / "public" / "NavalCommand" / "Units" / "Api" / "UnitId.h"
        with header.open("a", encoding="utf-8") as stream:
            stream.write(
                '\n#define HIDDEN_ORDER_HEADER <NavalCommand/Orders/Api/Request.h>\n'
                '#include HIDDEN_ORDER_HEADER\n'
            )
        self.assert_rejected(self.configure(), r"macro/nonliteral public include is forbidden")

    def test_reserved_environment_boundary(self):
        environment = self.root / "public" / "NavalCommand" / "Environment" / "Api"
        environment.mkdir(parents=True)
        (environment / "Forbidden.h").write_text(
            "#pragma once\n#include <NavalCommand/Units/Api/UnitId.h>\n"
            "namespace NavalCommand::Environment::Api {}\n",
            encoding="utf-8",
        )
        manifest = self.configure("add_library(Environment.Api INTERFACE)\ntarget_link_libraries(Environment.Api INTERFACE Units.Api)")
        self.assert_rejected(manifest, r"forbidden include edge Environment.Api -> Units.Api")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--cmake", default="cmake")
    arguments, unittest_arguments = parser.parse_known_args()
    CMAKE = arguments.cmake
    unittest.main(argv=[__file__] + unittest_arguments)
