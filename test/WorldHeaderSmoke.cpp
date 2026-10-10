#include <NavalCommand/World/Api/Stock.h>
#include <NavalCommand/World/Api/View.h>
#include <type_traits>

namespace World = NavalCommand::World::Api;
namespace Orders = NavalCommand::Orders::Api;
static_assert(std::is_same_v<decltype(World::Unit::orders)::value_type, Orders::Eligibility>);
static_assert(std::is_aggregate_v<World::Unit>);
static_assert(std::is_aggregate_v<World::View>);
static_assert(std::is_aggregate_v<World::Stock::LaunchOption>);

int main()
{
	World::Unit unit{"unit", "Friendly", {61.96, -10.37, std::nullopt}, std::nullopt, 1.0, {{"waypoint", Orders::Availability::Executable, "", "degrees"}}};
	World::Track track{"track", {61.0, -10.0, std::nullopt}, 1.0, "observer"};
	World::Stock::LaunchOption launchOption{"loadout", Orders::Availability::Executable, ""};
	World::Facility facility{"facility", {{"class", "squadron", 2, {launchOption}}}, 0, 1.0};
	World::View view{"session", "observer", true, false, 7, 1.0, {unit}, {track}, {facility}};
	const bool orderAndPositionAreValid = view.units.front().orders.front().availability == Orders::Availability::Executable &&
		!view.units.front().position.altitudeMeters;
	const bool stockOptionIsValid = view.facilities.front().stocks.front().unreservedCount == 2 &&
		view.facilities.front().stocks.front().launchOptions.front().loadout == "loadout";
	return orderAndPositionAreValid && stockOptionIsValid ? 0 : 1;
}
