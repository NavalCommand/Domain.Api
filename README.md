# Domain.Api

Operational contracts include explicit waypoint replace/append modes, copied planned-route receipts, generic facility launch arguments and distinct preparation/spawn/airborne stages. Backend support and current executable eligibility remain separate; omitted waypoint mode retains idle-only meaning. No game types or transport dependencies are introduced. See [contract implementation](../Docs/Tasks/006/TASK006_IMPLEMENTATION.md).

Operational C++ value contracts, independent of transport, serialization, simulators and hosting. Read the authoritative [Docs rules](../Docs/AGENTS.md), [architecture](../Docs/ARCHITECTURE.md), [module structure](../Docs/MODULE_STRUCTURE.md) and [code style](../Docs/CODE_STYLE.md) before changes.


Consumers link the domain target they use. `Gateway.Api` publicly links both and retains canonical Protobuf payloads, conversion and provider interfaces. There are no C# domain duplicates or third-party dependencies here.

From a VS 2026 x64 developer shell with CMake 4.2+ and Ninja:

```powershell
cmake --preset windows-msvc-release -DFETCHCONTENT_SOURCE_DIR_NCBUILD=/absolute/path/to/Build.CMake
cmake --build o/windows-msvc-release
ctest --test-dir o/windows-msvc-release --output-on-failure --no-tests=error
```

Debug uses `windows-msvc-debug`; Linux Clang presets are provided but have not been verified on Windows. Shared Build.CMake owns C++26 policy. MSVC uses `/std:c++latest` and static CRT (`/MT`, `/MTd`). No vcpkg manifest or external package is needed. Independent orders-only and world-only header consumers in `test/` exercise the target exports without Gateway.Api.

The repository is initially local and unpublished. Consumers declare `https://github.com/NavalCommand/Domain.Api.git` with `main`, and register the local checkout in their ignored top-level `Build.Local.cmake` through `NavalCommandSetDependencyPath`. That registration applies transitively. Build.CMake itself uses the standard bootstrap override above. Publication is required before ordinary public-remote builds can resolve Domain.Api; no push is implicit in local builds. All generated files belong under `o/`.
## Composed world contracts

`World.Api` exposes one `UnitInstance` shape and one `View::Instances` collection. Tagged subjects distinguish own-unit authority from observer tracks. Components carry explicit Known/Estimated/Unknown values; equipment coverage distinguishes complete empty from unknown. Catalog definitions use one composable `EquipmentType` and definitive resolved loadouts. Catalog retrieval and Sea Power equipment extraction remain future work.

The canonical world Protobuf directly mirrors these components. Schema version 2 intentionally replaces the split world schema; producers and consumers must use the same checkout graph. There are no compatibility projections. See [Task 014 report](../Docs/Tasks/014/REPORT.md).
