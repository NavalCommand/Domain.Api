# Domain.Api

Simulator- and gateway-independent C++23 value contracts. Public headers are organized by domain under `public/NavalCommand/<Domain>/Api/`; consumers link the matching header-only `.Api` target. Contributor and architecture rules are maintained in [`Docs/AGENTS.md`](../Docs/AGENTS.md), [`Docs/ARCHITECTURE.md`](../Docs/ARCHITECTURE.md), [`Docs/MODULE_STRUCTURE.md`](../Docs/MODULE_STRUCTURE.md), and [`Docs/CODE_STYLE.md`](../Docs/CODE_STYLE.md).

## Domain ownership and direct dependencies

| Target | Responsibility | Direct dependencies |
|---|---|---|
| `Physics.Api` | Physical quantities and positions | None |
| `Uncertainty.Api` | Values for known or unknown facts and resolutions | None |
| `Error.Api` | Shared error and result contracts | None |
| `Resources.Api` | Resource identifiers, definitions, and values | `Error.Api` |
| `Equipment.Api` | Equipment instances, loadouts, effects, damage, and providers | `Error.Api`, `Physics.Api`, `Resources.Api` |
| `Factions.Api` | Faction identity, alignment, and provider contracts | `Error.Api` |
| `Units.Api` | Authoritative unit identity, type, faction, kinematics, equipment, and optional aircraft state | `Equipment.Api`, `Error.Api`, `Factions.Api`, `Physics.Api` |
| `Observations.Api` | Observer-specific contact identity and uncertain observations | `Equipment.Api`, `Error.Api`, `Factions.Api`, `Physics.Api`, `Units.Api`, `Uncertainty.Api` |
| `Operations.Api` | Current unit activity, navigation, air operations, and read-only unit-state access | `Equipment.Api`, `Error.Api`, `Observations.Api`, `Physics.Api`, `Units.Api`, `Uncertainty.Api` |
| `Orders.Api` | Submitted command payloads and execution state | `Equipment.Api`, `Error.Api`, `Physics.Api`, `Units.Api` |
| `Environment.Api` | Terrain, weather, and time provider contracts | `Error.Api`, `Physics.Api` |
| `Simulation.Api` | Simulation pause and time-compression contracts | `Error.Api` |

The domain direction is acyclic. In particular, `Observations.Api` may use authoritative unit types, and `Operations.Api` may depend on both units and observations. `Units.Api` depends on neither observations nor operations.

## Units, observations, operations, and orders

**Units represent authoritative unit state; observations represent observer-specific information; operations represent current unit behavior; orders represent requested behavior.**

`Units::Api::Instance` contains authoritative identity, name, type, faction, kinematics, equipment, and an optional aircraft instance. It does not contain activity, navigation, or air-operations state, and it does not depend on observer-specific identifiers or uncertainty types.

`Observations::Api::Id` identifies an observer-side contact and is distinct from `Units::Api::Id`, which identifies an authoritative unit. An observation may be unknown, ambiguous, or uncorrelated with a known true unit. Observation values use the uncertainty contracts where information is not fully known.

`Operations::Api::UnitState` is a separate projection of current operational behavior. It contains an `Activity` value and optional navigation and air-operations values. The `std::monostate` activity means unknown or unreported activity, distinct from `Idle`; absent navigation or air-operations data is left absent. An activity that refers to an observed contact uses `Observations::Api::Id`, including engagement targets and evasive-maneuver danger sources. `Operations::Api::IProvider` accepts a true `Units::Api::Id` for the friendly unit whose state is requested; its implementation is scoped to the controlling faction.

`Orders.Api` remains separate from `Operations.Api`: an order records requested behavior, while operations report current behavior. `Orders::Api::ExecutionRequest::Executor` remains a `Units::Api::Id` because it identifies the friendly unit executing the request. The order model does not use the operations projection.

## Testing

GoogleTest and GoogleMock are test-only dependencies managed in vcpkg manifest mode. The pinned registry baseline and `gtest` dependency are declared in [`vcpkg.json`](vcpkg.json); no GoogleTest source is fetched or vendored by this repository.

Install vcpkg, bootstrap it, and set `VCPKG_ROOT` to its checkout before configuring. For example, in PowerShell:

```powershell
$env:VCPKG_ROOT = "C:\path\to\vcpkg"
& "$env:VCPKG_ROOT\bootstrap-vcpkg.bat"
```

On Linux, use the vcpkg checkout path for `VCPKG_ROOT` and run `"$VCPKG_ROOT/bootstrap-vcpkg.sh"`. The Windows presets select `x64-windows-static`, which uses the static MSVC runtime requested by the presets. Linux presets use `x64-linux` and Clang.

Configure, build, and run CTest with the matching presets:

```powershell
cmake --preset windows-msvc-debug
cmake --build --preset windows-msvc-debug
ctest --preset windows-msvc-debug
```

```sh
cmake --preset linux-clang-debug
cmake --build --preset linux-clang-debug
ctest --preset linux-clang-debug
```

Use the corresponding `*-release` preset names for Release builds. CTest discovers each GoogleTest case and also runs architecture validation plus the generated independent public-header compilation check.

Manually maintained tests mirror the public namespace directories: for example, `public/NavalCommand/Units/Api/Instance.h` is tested in `test/NavalCommand/Units/Api/InstanceTest.cpp`. Name each file `<TypeName>Test.cpp`, keep assertions with the contract they cover, and use ordinary `TEST` or `TEST_F` cases. To add a test for a public type, add a source under its matching `test/NavalCommand/<Domain>/Api/` directory and link through the existing `domain-tests` target. CMake separately generates one build-directory translation unit per public header; each includes only that header and links through its owning domain target.

Mocks mirror the same domain structure under `mock/` and use `<InterfaceName>Mock.h`, for example `mock/NavalCommand/Units/Api/IInstanceProviderMock.h`. Put the mock in the interface's namespace, include the public interface, inherit it, and declare every pure virtual method with `MOCK_METHOD` using the exact signature. Add an `EXPECT_CALL` compilation/use case in the matching `test/NavalCommand/<Domain>/Api/<InterfaceName>MockTest.cpp`. The `mock/` include directory is exposed only to the test executable; it is not part of any public `.Api` target.

CTest also validates public-header ownership and direct domain dependencies, rejects forbidden dependency edges and cycles, and runs negative architecture fixtures. The domain dependency direction remains acyclic, including `Operations.Api → Observations.Api → Units.Api`; `Units.Api` does not depend on observations or operations.
