#include <NavalCommand/Observations/Api/AircraftSelection.h>
#include <NavalCommand/Observations/Api/ObserverId.h>
#include <NavalCommand/Observations/Api/UnitObservation.h>
#include <NavalCommand/Uncertainty/Api/Knowledge.h>
#include <cstdint>
#include <string>
#include <type_traits>

namespace Observations = NavalCommand::Observations::Api;
namespace Uncertainty = NavalCommand::Uncertainty::Api;
namespace Catalog = NavalCommand::Catalog::Api;

static_assert(!std::is_same_v<Observations::ObservationId, Observations::ObserverId>);
static_assert(std::is_same_v<decltype(Observations::UnitObservation::Identity), Observations::ObservationId>);
static_assert(std::is_same_v<decltype(Observations::UnitObservation::Type), Uncertainty::Knowledge<Catalog::UnitTypeId>>);
static_assert(std::is_same_v<decltype(Observations::UnitObservation::Name), Uncertainty::Knowledge<std::string>>);

int main()
{
	Observations::UnitObservation falseContact;
	falseContact.Identity = {"observer-a-contact-9"};
	falseContact.Name = Uncertainty::Knowledge<std::string>::Known("Carrier one");
	falseContact.Type = Uncertainty::Knowledge<Catalog::UnitTypeId>::Estimated({"missile"}, "radar return");
	Observations::UnitObservation fused = falseContact;
	fused.Identity = {"observer-a-fused-contact"};
	fused.Name = {};
	Observations::AirOperationsObservation airOperations;
	using Entries = Uncertainty::ObservedCollection<Observations::AirOperationsObservation::AircraftInventoryEntry>;
	using Loadouts = Uncertainty::ObservedCollection<Catalog::LoadoutId>;
	airOperations.Inventory = {
		Entries::Coverage::Complete,
		{{Uncertainty::Knowledge<Catalog::UnitTypeId>::Known({"helicopter"}),
		  Uncertainty::Knowledge<std::string>::Known("squadron-a"),
		  Uncertainty::Knowledge<std::uint32_t>::Known(4),
		  Loadouts{Loadouts::Coverage::Complete, {{"strike"}, {"patrol"}}}}}};
	falseContact.AirOperations = airOperations;
	const Observations::AircraftSelection launchSelection{{"helicopter"}, "squadron-a", {"patrol"}};
	const auto& stock = falseContact.AirOperations->Inventory.Items()[0];
	return falseContact.Identity.Value != fused.Identity.Value &&
		falseContact.Name.IsKnown() && !fused.Name.HasValue() &&
		!falseContact.Kinematics.Position.HasValue() &&
		stock.UnreservedCount.Value() == 4 && stock.Loadouts.Items().size() == 2 &&
		launchSelection.Loadout.Value == stock.Loadouts.Items()[1].Value ? 0 : 1;
}
