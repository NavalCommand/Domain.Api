#include <NavalCommand/World/Api/RecordedSnapshots.h>
#include <type_traits>

namespace World = NavalCommand::World::Api;
namespace Units = NavalCommand::Units::Api;
namespace Catalog = NavalCommand::Catalog::Api;
namespace Uncertainty = NavalCommand::Uncertainty::Api;
namespace Observations = NavalCommand::Observations::Api;

static_assert(!std::is_same_v<Units::UnitId, Observations::ObservationId>);
static_assert(std::is_same_v<decltype(World::SimulationSnapshot::Units), std::vector<Units::UnitInstance>>);
static_assert(std::is_same_v<decltype(World::ObserverSnapshot::Units), std::vector<Observations::UnitObservation>>);
static_assert(std::is_same_v<decltype(World::ObserverUnitRelationship::Observation), Observations::ObservationId>);

int main()
{
	World::RecordedSnapshots recording;
	recording.Truth.SessionId = "session";
	recording.Truth.Units.push_back({Units::UnitId{"truth-1"}});
	Units::UnitInstance carrier;
	carrier.Identity = {"truth-carrier"};
	carrier.Type = Catalog::UnitTypeId{"carrier"};
	carrier.AirOperations.emplace();
	carrier.AirOperations->PendingOperations = 0;
	recording.Truth.Units.push_back(carrier);
	recording.Truth.Units.push_back({Units::UnitId{"truth-2"}});
	World::ObserverSnapshot observerA;
	observerA.SessionId = "session";
	observerA.Observer = {"blue"};
	observerA.Units.push_back({Observations::ObservationId{"blue-contact-1"}});
	Observations::UnitObservation observedCarrier;
	observedCarrier.Identity = {"blue-carrier"};
	observedCarrier.Type = Uncertainty::Knowledge<Catalog::UnitTypeId>::Known({"carrier"});
	observedCarrier.AirOperations.emplace();
	observerA.Units.push_back(observedCarrier);
	observerA.Units.push_back({Observations::ObservationId{"blue-fused-contact"}});
	World::ObserverSnapshot observerB;
	observerB.SessionId = "session";
	observerB.Observer = {"red"};
	observerB.Units.push_back({Observations::ObservationId{"red-contact-7"}});
	recording.Perspectives = {observerA, observerB};
	recording.Associations.push_back({observerA.Observer, observerA.Units[0].Identity, recording.Truth.Units[0].Identity});
	recording.Associations.push_back({observerB.Observer, observerB.Units[0].Identity, recording.Truth.Units[0].Identity});
	recording.Associations.push_back({observerA.Observer, observerA.Units[2].Identity, recording.Truth.Units[0].Identity});
	recording.Associations.push_back({observerA.Observer, observerA.Units[2].Identity, recording.Truth.Units[2].Identity});
	const bool independentObserverHandles =
		recording.Perspectives[0].Units[0].Identity.Value != recording.Perspectives[1].Units[0].Identity.Value;
	const bool supportsManyToOneFusion = recording.Associations[2].Observation == recording.Associations[3].Observation &&
		recording.Associations[2].Unit != recording.Associations[3].Unit;
	const bool separatesAirOperationsTruthAndObservation = recording.Truth.Units[1].AirOperations->PendingOperations == 0 &&
		!recording.Perspectives[0].Units[1].AirOperations->PendingOperations.HasValue();
	return recording.Associations.size() == 4 && independentObserverHandles && supportsManyToOneFusion &&
		separatesAirOperationsTruthAndObservation ? 0 : 1;
}
