# Domain.Api

Simulator- and gateway-independent C++23 value contracts. Public headers are organized by domain under `public/NavalCommand/<Domain>/Api/`; consumers link the corresponding header-only `NavalCommand.<Domain>.Api` target. Contributor and architecture rules are maintained in [`Docs/AGENTS.md`](../Docs/AGENTS.md), [`Docs/ARCHITECTURE.md`](../Docs/ARCHITECTURE.md), [`Docs/MODULE_STRUCTURE.md`](../Docs/MODULE_STRUCTURE.md), and [`Docs/CODE_STYLE.md`](../Docs/CODE_STYLE.md).

## Domain ownership and direct dependencies

| Target | Responsibility | Direct dependencies |
|---|---|---|
| `NavalCommand.Physics.Api` | Physical quantities and positions | None |
| `NavalCommand.Uncertainty.Api` | Values for known or unknown facts and resolutions | None |
| `NavalCommand.Error.Api` | Shared error and result contracts | None |
| `NavalCommand.Classification.Api` | Affiliation, taxonomy hierarchy, and designed-role vocabulary | None |
| `NavalCommand.Resources.Api` | Resource identifiers, definitions, and values | `NavalCommand.Error.Api` |
| `NavalCommand.Equipment.Api` | Equipment instances, loadouts, effects, damage, and providers | `NavalCommand.Classification.Api`, `NavalCommand.Error.Api`, `NavalCommand.Physics.Api`, `NavalCommand.Resources.Api` |
| `NavalCommand.Factions.Api` | Faction identity, alignment, and provider contracts | `NavalCommand.Classification.Api`, `NavalCommand.Error.Api` |
| `NavalCommand.Units.Api` | Authoritative unit identity, type, faction, kinematics, equipment, and optional aircraft state | `NavalCommand.Classification.Api`, `NavalCommand.Equipment.Api`, `NavalCommand.Error.Api`, `NavalCommand.Factions.Api`, `NavalCommand.Physics.Api` |
| `NavalCommand.Observations.Api` | Observer-specific contact identity and uncertain observations | `NavalCommand.Classification.Api`, `NavalCommand.Equipment.Api`, `NavalCommand.Error.Api`, `NavalCommand.Factions.Api`, `NavalCommand.Physics.Api`, `NavalCommand.Units.Api`, `NavalCommand.Uncertainty.Api` |
| `NavalCommand.Operations.Api` | Current unit activity, navigation, air operations, and read-only unit-state access | `NavalCommand.Equipment.Api`, `NavalCommand.Error.Api`, `NavalCommand.Observations.Api`, `NavalCommand.Physics.Api`, `NavalCommand.Units.Api`, `NavalCommand.Uncertainty.Api` |
| `NavalCommand.Orders.Api` | Submitted command payloads and execution state | `NavalCommand.Equipment.Api`, `NavalCommand.Error.Api`, `NavalCommand.Physics.Api`, `NavalCommand.Units.Api` |
| `NavalCommand.Environment.Api` | Terrain, weather, and time provider contracts | `NavalCommand.Error.Api`, `NavalCommand.Physics.Api` |
| `NavalCommand.Simulation.Api` | Simulation pause and time-compression contracts | `NavalCommand.Error.Api` |

The domain direction is acyclic. In particular, `NavalCommand.Observations.Api` may use authoritative unit types, and `NavalCommand.Operations.Api` may depend on both units and observations. `NavalCommand.Units.Api` depends on neither observations nor operations.

## Units, observations, operations, and orders

**Units represent authoritative unit state; observations represent observer-specific information; operations represent current unit behavior; orders represent requested behavior.**

`Units::Api::Instance` contains authoritative identity, name, type, faction, kinematics, equipment, a current loadout ID (including an empty configuration), and an optional aircraft instance. It does not contain activity, navigation, or air-operations state, and it does not depend on observer-specific identifiers or uncertainty types.

`Observations::Api::Id` identifies an observer-side contact and is distinct from `Units::Api::Id`, which identifies an authoritative unit. An observation may be unknown, ambiguous, or uncorrelated with a known true unit. Observation values use the uncertainty contracts where information is not fully known. `Observations::Api::Instance::Type` resolves one observer-supported classification level: exact `Units::Api::TypeId`, `Classification::Api::SubCategory`, `Classification::Api::Category`, `Classification::Api::Dimension`, or unknown. A more precise variant must never be inferred from hidden native truth. `CurrentLoadout` is `Exact<Equipment::Api::LoadoutId>`: unknown or a known selected loadout (including an empty configuration).

`Operations::Api::UnitState` is a separate projection of current operational behavior. It contains an `Activity` value and optional navigation and air-operations values. The `std::monostate` activity means unknown or unreported activity, distinct from `Idle`; absent navigation or air-operations data is left absent. An activity that refers to an observed contact uses `Observations::Api::Id`, including engagement targets and evasive-maneuver danger sources. `Operations::Api::IProvider` accepts a true `Units::Api::Id` for the friendly unit whose state is requested; its implementation is scoped to the controlling faction.

`NavalCommand.Orders.Api` remains separate from `NavalCommand.Operations.Api`: an order records requested behavior, while operations report current behavior. `Orders::Api::ExecutionRequest::Executor` remains a `Units::Api::Id` because it identifies the friendly unit executing the request. The order model does not use the operations projection.

## Classification semantics

`Units::Api::Type` stores exactly one authoritative `UnitSubCategory`. The constexpr `Classification::Api::GetCategory(SubCategory)` function is declared in `SubCategory.h`, and `GetDimension(Category)` in `Category.h`. Together, these derive the complete classification hierarchy without redundant unit-type fields. These functions require declared enum values; adapters must validate untrusted numeric codes before casting.

An `Observations::Api::Instance::Type` is an independent observer-specific `Resolution<TypeId, SubCategory, Category, Dimension>`; it can report the less specific classification actually supported by the selected observer. Do not promote an observation using hidden native type data.

The domain taxonomy includes generic fallback subcategories such as `Missile`, `Torpedo`, `SurfaceVessel`, and `Submarine`, alongside specialized values such as `CruiseMissile`, `HeavyweightTorpedo`, `Destroyer`, and `AttackSubmarine`. It may be more precise than Sea Power's native runtime types: native types without a reliable subtype distinction can use a generic fallback, while supported specialized classifications remain part of the domain vocabulary.

`Units::Api::Type::PlatformRoles` describes roles intrinsic to the platform, independently of its selected loadout. `Equipment::Api::Loadout::Roles` describes additional roles supported by that configuration. Both represent designed military purposes, not active missions, orders, or readiness. Configuration-dependent roles belong on the loadout, and platform roles always contribute to the complete role set. Even a platform without configurable equipment should have a named standard/empty loadout in a complete type catalogue.

`Units::Api::Type::PrimaryPlatformRole` is an optional, explicit intrinsic mission
used to choose a presentation specialization. It uses the same engine-independent
`Classification::Api::Role` enum and, when present, must also occur in `PlatformRoles`.
It is independent of subcategory, the current loadout and active missions. Absence
means unspecified; consumers must not choose the first role or a hard-coded
priority from the full capability list. The gateway validates membership and enum
values. Primary role does not change `GetRoles` union semantics.
`Role::GuidedMissile` denotes a platform's guided-missile warfare capability,
independently of its physical class. A guided missile cruiser remains a Cruiser
subcategory; its primary role can be GuidedMissile.

For a configuration, the effective roles are `PlatformRoles ∪ Loadout::Roles`. `Units::Api::GetRoles(Type)` returns the deduplicated union of `PlatformRoles` and every loadout's roles, describing all roles potentially supported by the type rather than a currently selected configuration. Ordering is deterministic: platform roles first, followed by roles in loadout declaration order, with each vector's order preserved. Empty role vectors mean no roles are specified.

`Units::Api::Instance::CurrentLoadout` is a loadout ID and must correspond to a loadout of the referenced type. The observer's `Exact<LoadoutId>` represents unknown or known selected configuration; merely identifying the type does not disclose which configuration is active.

Missile flight class (for example, cruise/ballistic) must not be confused with intended target (air/surface/land); the latter belongs to sourced roles and equipment/weapon properties. The classification vocabulary is simulator-independent, not a complete APP-6 symbol catalogue. A future symbology adapter maps this model to NATO symbols.

## Build and testing

CMake provides a C++23 `INTERFACE` library for each domain, named `NavalCommand.<Domain>.Api` (for example, `NavalCommand.Units.Api`). The domain libraries have no GoogleTest dependency. The sole C++ test executable is `NavalCommand.Domain.Api.Test`.

### Prerequisites

The checked-in CMake presets currently support **Windows x64 with MSVC and Ninja** (Debug and Release). Run CMake from an environment where `cl.exe` and Ninja are available, such as an MSVC developer shell.

GoogleTest and GoogleMock are test-only dependencies installed through vcpkg manifest mode from `vcpkg.json`. Install and bootstrap vcpkg, then set `VCPKG_ROOT` to its checkout:

```powershell
$env:VCPKG_ROOT = "C:\path\to\vcpkg"
& "$env:VCPKG_ROOT\bootstrap-vcpkg.bat"
```

The Windows presets use the `x64-windows-static` vcpkg triplet, matching the statically linked MSVC runtime specified by the presets.

### Configure, build, and run tests

From the repository root:

```powershell
cmake --preset windows-msvc-debug
cmake --build o/windows-msvc-debug
ctest --test-dir o/windows-msvc-debug --output-on-failure
```

For Release, replace `windows-msvc-debug` with `windows-msvc-release` in all three commands. The presets define **configure presets only**; they do not define separate CMake build or CTest presets.

`test/CMakeLists.txt` compiles all C++ tests into `NavalCommand.Domain.Api.Test` and registers individual GoogleTest cases with CTest via `gtest_discover_tests()`. There is no separate generated per-header compilation suite or Python architecture-test suite.

### Test and mock organization

Tests mirror the public namespace/folder hierarchy, with one `<TypeName>Test.cpp` file per tested contract:

```text
public/NavalCommand/Units/Api/Instance.h
test/NavalCommand/Units/Api/InstanceTest.cpp
```

Add new C++ tests under `test/NavalCommand/<Domain>/Api/` using GoogleTest's `TEST` or `TEST_F`. CMake discovers their `.cpp` sources for the existing `NavalCommand.Domain.Api.Test` executable. Keep compile-time `static_assert` checks for type-level invariants.

GoogleMock definitions live in `mock/`, following the same hierarchy:

```text
public/NavalCommand/Units/Api/IInstanceProvider.h
mock/NavalCommand/Units/Api/IInstanceProviderMock.h
test/NavalCommand/Units/Api/IInstanceProviderMockTest.cpp
```

Mocks retain their public interface's namespace, inherit that interface, and implement its virtual methods with `MOCK_METHOD` using the exact signatures. Mock tests can use `EXPECT_CALL`. The `mock/` include directory and GoogleTest/GoogleMock dependencies belong to the test executable only, not the domain libraries.
