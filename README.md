# Domain.Api

Transport-, simulator- and gateway-independent operational C++ value contracts. Read the authoritative [contributor rules](../Docs/AGENTS.md), [architecture](../Docs/ARCHITECTURE.md), [module structure](../Docs/MODULE_STRUCTURE.md) and [code style](../Docs/CODE_STYLE.md) before changes.

## Ownership and direct dependencies

Every populated namespace mirrors `public/NavalCommand/<Domain>/Api/` and owns an independent header-only `INTERFACE` target. Consumers link the target whose contracts they use.

| Target | Responsibility | Allowed direct dependencies |
|---|---|---|
| `Physics.Api` | Physical quantities and position | None |
| `Uncertainty.Api` | Minimal two-state `Exact<T>` value | None |
| `Catalog.Api` | Definitive catalog definitions, IDs, loadouts, capability effects/operations and resource definitions | `Physics.Api` |
| `Units.Api` | Authoritative simulation identity, kinematics, equipment and supported true state | `Catalog.Api`, `Physics.Api` |
| `Observations.Api` | Observer-specific contact identity, uncertain unit/equipment state, evidence and observed navigation/air operations | `Catalog.Api`, `Physics.Api`, `Uncertainty.Api` |
| `Orders.Api` | Typed command requests/results and observer-specific order-availability overlay | `Observations.Api`, `Physics.Api` (Uncertainty.Api is allowlisted if needed; current headers do not use it) |
| `Environment.Api` (reserved) | Future verified environment facts | `Physics.Api`, `Uncertainty.Api` |
| `World.Api` | Separate simulation and observer snapshots, membership relationships, privileged capture labels | `Units.Api`, `Observations.Api`, `Physics.Api`, `Uncertainty.Api` |

`Environment.Api` currently has no target or headers because no verified environment contract is implemented. The checker enforces this ownership boundary. The maintained graph checker validates canonical public-header paths, exact allowlisted direct includes and target edges, cycles, populated domain/target parity, and exact correspondence between direct header and target dependencies. It rejects macros, relative includes, aliases, generator-expression links, unknown links and reserved-boundary violations. Tests inject forbidden edges into copied headers and actual CMake target declarations.

## Simulation truth and observations

`Units::Api::UnitId` identifies an authoritative simulated tactical entity. `UnitInstance` contains definite expressed properties: optional catalog type; independently optional definite position, speed, heading and course; optional equipment inventory, route, flight and air-operations state. Equipment operational facts, resources and air-inventory counts are also optional when the source does not express them. The model contains no observer/contact ID, uncertainty wrapper or eligibility and does not invent zero/default truth. An independently simulated launched missile/projectile may be a `UnitInstance` with its own ID/type/kinematics; it need not have aircraft, crew, hull, or air-operations components. Carried missile inventory is launcher equipment/resource state, never the launched projectile entity.

`Observations::Api::ObserverId` scopes a perspective; `ObservationId` identifies an observer-side representation and is distinct from true `UnitId`. `UnitObservation` uses `Exact<T>` only for wholly known or unknown facts; its position is one `ObservedPosition` variant with either `Exact<Physics::Api::Position>` or `PartiallyLocalizedPosition` (including optional source-backed major/minor/orientation error ellipse). Own exact positions remain distinct from approximate contact centers. Equipment and contributor vectors list only currently reported/source-supported items; empty does not prove exhaustive absence. A contributor's observer handle is an `ObservationId`, never a truth `UnitId`; aggregate plotted contacts without supported individual attribution have no fabricated contributors. Supported own names remain known, while contacts without source-backed names remain Unknown. Contacts may be false, duplicate, fused or ambiguous; no one-to-one truth mapping exists in operational observation types. Snapshot capture and exact measurement times remain distinct.

`World::Api::SimulationSnapshot` is privileged truth and authoritative `UnitId` membership; `FactionId` and `TaskForceId` are distinct World-owned identifiers. `ObserverSnapshot` is one perspective containing only Observations types and relationships keyed by `ObservationId`, with uncertain affiliations. There is no mixed View, truth ID, hidden truth relation, or correlation in an observer snapshot. `RecordedSnapshots` is a privileged in-memory capture contract that may hold truth, independent perspectives and zero-or-more `ObservationAssociation` rows; vector associations support many-to-many mappings and are never emitted through observer APIs. These contracts do not claim deterministic engine replay. Decision/outcome capture that depends on Orders belongs in an internal gateway recorder envelope, not in World and not in public RPC.

## Catalog, resources and orders

Catalog IDs are distinct strong types. Catalog definitions are definitive only for the resolved context/source subset; absent support remains absent rather than guessed. UnitType.Platform is optional, so projectile unit types need not be falsely classified as surface/land/air platforms. When platform category is supported, Aircraft is classified as FixedWingAircraft or RotaryWingAircraft (a helicopter is rotary-wing aircraft), alongside meaningful SurfaceVessel, Submarine and LandPlatform categories. One `EquipmentType` represents one operational capability with effects and operations. `Use` invokes once; `SetActive` requests operating state. No duplicated CapabilityIndex, generic Active/Passive/Guided mode, or invocation-duration field exists. Resource values preserve exact discrete `uint64_t` counts or continuous `double` quantities; definitions own representation, SI measurement unit, and consumable/allocatable accounting semantics.

Orders are overlays over observer handles. `OrderAvailability`, `Request` and observer-visible results use `ObserverId` and `ObservationId`, with session/freshness context; typed order kinds replace arbitrary eligibility strings, and each request has exactly one variant payload (`RouteCommand` or `LaunchAircraft`). Route results preserve waypoint labels through `Observations::Api::ObservedRoutePoint`. Observed air-inventory counts are grouped by aircraft type and squadron; supported loadouts are separate choices, not repeated stock. A launch order uses `Observations::Api::AircraftSelection` combining type, squadron and one loadout, not an opaque permission token. Inventory does not imply launch permission. The privileged execution provider must revalidate current authority, freshness, native safety and preconditions, then resolve the observation handle privately. No Orders header depends on Units or World.

## Tests and verification

CTest runs the architecture checker/negative fixtures, standalone compilation for every public header through its owning target, and semantic smoke consumers for Physics, Uncertainty, Catalog, Units, Observations, Orders and World. Semantic fixtures cover truth versus uncertain observations, independent observer IDs, ambiguous/fused contacts, projectile entities without platform assumptions, observer-scoped orders, independent world snapshots, and privileged many-to-many recording associations. Parent integration is responsible for cross-repository builds and verification for this cutover.
