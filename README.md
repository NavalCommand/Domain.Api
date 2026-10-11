# Domain.Api

Transport-, simulator- and gateway-independent operational C++ value contracts. Read the authoritative [contributor rules](../Docs/AGENTS.md), [architecture](../Docs/ARCHITECTURE.md), [module structure](../Docs/MODULE_STRUCTURE.md) and [code style](../Docs/CODE_STYLE.md) before changes.

## Ownership and direct dependencies

Each populated namespace mirrors `public/NavalCommand/<Domain>/Api/` and owns an independent header-only `INTERFACE` target. Consumers link the target whose contracts they use; they do not add sibling include paths themselves.

| Target | Owns | Allowed direct dependencies |
|---|---|---|
| `Physics.Api` | Focused physical scalars and geodetic position | None |
| `Uncertainty.Api` | Generic `Knowledge<T>` and `ObservedCollection<T>` | None |
| `Catalog.Api` | Definitive catalog, strong catalog IDs, resolved loadouts, equipment effects/operations and resource definitions | `Physics.Api` |
| `Units.Api` | Observer identities, composed runtime units, equipment, navigation, aircraft and attached air-operations inventory | `Catalog.Api`, `Physics.Api`, `Uncertainty.Api` |
| `Orders.Api` | Typed requests/results, execution stages and separately discovered per-unit availability | `Units.Api`, `Physics.Api`, `Uncertainty.Api` |
| `Environment.Api` (reserved) | Future supported environment observations | `Physics.Api`, `Uncertainty.Api` |
| `World.Api` | Session/snapshot metadata, unit aggregation and membership overlay | `Units.Api`, `Environment.Api` when populated, `Physics.Api`, `Uncertainty.Api` |

`Environment.Api` currently has no header or target: no verified environment data is implemented. The architecture checker nevertheless enforces its ownership boundary. `World.Api` therefore links only its three populated direct dependencies. Neither `Units.Api` nor `World.Api` imports `Orders.Api`. Catalog definitions never import observer uncertainty. `Gateway.Api` composes a world snapshot with a separate order-availability overlay outside these domains.

## Operational semantics

- `Units::Api::UnitId` is one opaque observer/session-scoped observation handle for own units and contacts. It does not prove one real platform or command authority. Session changes invalidate provider handles. Authority and native safety are revalidated at dispatch; availability is not permission to bypass those checks.
- `UnitInstance` has identification, kinematics, equipment and optional navigation, aircraft and air-operations components. Orders and faction/task-force relationships are independent overlays keyed by the same `UnitId`. Airfields/carriers are units with `AirOperations`, never duplicate public facilities.
- `Knowledge<T>` defaults to unknown; known zero/false/empty are values, not unknown. `ObservedCollection<T>` distinguishes unknown, partial and complete coverage, rejects unknown-with-items and invalid coverage. Complete-empty equipment/resources/inventory confirms an empty applicable enumeration; unknown-empty does not. For resources, complete-empty means no applicable resources.
- `NavigationState::PlannedRoute` alone represents route knowledge: known-empty means inspected-empty; unknown means uninspected or unavailable. Route replace, append and idle-waypoint modes retain distinct behavior.
- Physics scalars express explicit meters, meters/second, seconds, degrees and radians. Positions are geodetic latitude/longitude, with optional altitude above mean sea level. Heading is body orientation; course-over-ground is movement direction, both clockwise from geodetic north. Unknown directions are never inferred from an unrelated simulator reading.
- `View::CapturedAt` is snapshot capture time in session operational seconds. Unit `ObservationMetadata::MeasuredAt` is the last actual measurement only when known. Cached enemy measurements stay unknown unless their genuine measurement time is available. Air-inventory `MeasuredAt` describes its actual sampling. Estimate `Source()` is an evidence trace, not an invented sensor identity; there is no duplicate top-level provenance string.
- Catalog IDs are strong types. Catalog data is definitive for one resolved content/session context; optional traits mean unmodeled/not applicable, not observer uncertainty. A helicopter is `Aircraft` with `RotaryWing` classification. No service-year/provider schema is introduced.
- One `EquipmentType` describes one operational capability with potentially multiple effects and operations, not necessarily one physical device. `Use` invokes once; `SetActive` requests activity state. Empty accepted-target kinds mean no designation. Target kinds are definitive catalog metadata; actual unit-designation payloads belong in Orders if implemented. Sonobuoy deployment is distinct from subsequent listening; invocation duration is not lasting-effect duration.
- Concrete guidance describes projectile control (`Autonomous`/`Command`), not generic operation modes. Optional sensing nominal range is an intrinsic capability constraint, not loadout geometry or runtime physical truth. Ambiguous shared `PhysicalTraits`, parallel capability indexes and action-derived durations are removed; unused installation geometry is deferred.
- One resource value model uses exact `uint64_t` discrete counts or continuous `double` values in the definition's SI unit. `ResourceDefinition` separately specifies numeric representation, measurement unit (`Count`, `Kilograms`, `CubicMeters`) and consumable versus allocatable accounting. Fits name capacity and initial inventory separately; operations name consumption versus reservation; instances report current quantities with explicit collection coverage. Fuel is not a charge count and jam channels are not ammunition. This is a definition, not an accounting engine.
- `AircraftSelection` identifies one inventory aircraft/squadron/loadout combination and is genuinely used by `Orders::FacilityLaunch`, avoiding an Orders-to-Catalog include dependency. Inventory reports selectors and observed counts; launch eligibility/reasons live only in discovery rows. Requests contain exactly one route or launch payload in a variant. Preparation, aircraft spawn and airborne stages remain distinct.
- Membership coverage and each faction/task-force value are observer-visible knowledge. Unknown enemy affiliation remains unknown; no privileged ownership inference is allowed.

Catalog retrieval, actual backend equipment extraction and supported environment acquisition remain outside this refactor's feature scope. Their absence is not represented by fabricated complete-empty observations.

## Architecture enforcement and fixtures

CTest runs `test/CheckArchitecture.py` against both direct exported-header includes and final direct `INTERFACE_LINK_LIBRARIES` properties exported after CMake configuration. It checks canonical namespace paths, the exact directed allowlist, cycles, missing targets and exact correspondence between actual public-header edges and target links. Relative/quoted or macro-based includes, external/unknown links, aliases and dependency generator expressions are rejected with actionable file/target diagnostics. The exporter reads raw direct properties: CMake 4.2 generator-expression property evaluation would otherwise expand transitive links. A shared public include root is not considered architectural enforcement by itself.

`test/ArchitectureTests.py` copies public headers into temporary fixtures and configures the real target declarations, then deliberately adds forbidden Units-to-Orders, Units-to-World and World-to-Orders includes and CMake links. It also exercises real cycles, missing links, aliases, external links, generator expressions, relative/macro includes and the reserved Environment boundary. These are maintained offline regression fixtures, not runtime scaffolding.

Every exported header independently compiles as its translation unit's sole domain include and links through its owning target. Separate Physics, Uncertainty, Catalog, Units, Orders and World executables consume only their own target. Semantic fixtures cover uncertainty boundaries, six equipment types (guided missile, radar, active ECM, chaff, sonobuoy and external tank), two resolved loadouts sharing definitions, integer/continuous resources, route knowledge, attached air inventory, typed discovery/request payloads and world memberships. Backend authority/revalidation and cross-language wire semantics are tested in the owning adapter repositories.

## Build and verification

From a VS 2026 x64 developer shell with CMake 4.2+, Ninja and Python 3:

```powershell
cmake --preset windows-msvc-release -DFETCHCONTENT_SOURCE_DIR_NCBUILD=/absolute/path/to/Build.CMake
cmake --build o/windows-msvc-release --parallel 8
ctest --test-dir o/windows-msvc-release --output-on-failure --no-tests=error
```

Debug uses `windows-msvc-debug`; Linux Clang presets are also provided. Shared Build.CMake owns C++26 policy. MSVC uses `/std:c++latest` and static CRT (`/MT`, `/MTd`). Domain.Api needs no vcpkg packages. Python is an architecture-test dependency, not a public runtime dependency. Generated files stay under `o/`.

Consumers declare `https://github.com/NavalCommand/Domain.Api.git` and may register the local checkout in an ignored top-level `Build.Local.cmake` through `NavalCommandSetDependencyPath`; that registration applies transitively. Build.CMake itself uses the normal FetchContent bootstrap override above. No local build implies permission to push or deploy.
