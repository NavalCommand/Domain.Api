# Domain.Api

Operational contracts include explicit waypoint replace/append modes, copied planned-route receipts, generic facility launch arguments and distinct preparation/spawn/airborne stages. Backend support and current executable eligibility remain separate; omitted waypoint mode retains legacy idle-only meaning. No game types or transport dependencies are introduced. See [contract implementation](../Docs/Tasks/006/TASK006_IMPLEMENTATION.md).

Operational C++ value contracts, independent of transport, serialization, simulators and hosting. Read the authoritative [Docs rules](../Docs/AGENTS.md), [architecture](../Docs/ARCHITECTURE.md), [module structure](../Docs/MODULE_STRUCTURE.md) and [code style](../Docs/CODE_STYLE.md) before changes.

`Orders.Api` and `World.Api` are separate header-only INTERFACE CMake targets defined in `src/`. `World.Api` transitively links `Orders.Api` for per-unit eligibility; orders has no world dependency. Public namespace-mirrored headers live under `public/NavalCommand/{Orders,World}/Api/`. Existing include spellings, aggregates, defaults and enum values are preserved. `Order.h` remains the compatibility umbrella; existing camelCase public members are deliberate compatibility exceptions.

Consumers link the domain target they use. `Gateway.Api` publicly links both and retains canonical Protobuf payloads, conversion and provider interfaces. There are no C# domain duplicates or third-party dependencies here.

From a VS 2026 x64 developer shell with CMake 4.2+ and Ninja:

```powershell
cmake --preset windows-msvc-release -DFETCHCONTENT_SOURCE_DIR_NCBUILD=/absolute/path/to/Build.CMake
cmake --build o/windows-msvc-release
ctest --test-dir o/windows-msvc-release --output-on-failure --no-tests=error
```

Debug uses `windows-msvc-debug`; Linux Clang presets are provided but have not been verified on Windows. Shared Build.CMake owns C++26 policy. MSVC uses `/std:c++latest` and static CRT (`/MT`, `/MTd`). No vcpkg manifest or external package is needed. Independent orders-only and world-only header consumers in `test/` exercise the target exports without Gateway.Api.

The repository is initially local and unpublished. Consumers declare `https://github.com/NavalCommand/Domain.Api.git` with `main`, and register the local checkout in their ignored top-level `Build.Local.cmake` through `NavalCommandSetDependencyPath`. That registration applies transitively. Build.CMake itself uses the standard bootstrap override above. Publication is required before ordinary public-remote builds can resolve Domain.Api; no push is implicit in local builds. All generated files belong under `o/`.
