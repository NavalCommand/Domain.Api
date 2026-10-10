#include <NavalCommand/World/Api/View.h>
#include <type_traits>

namespace World = NavalCommand::World::Api;
namespace Orders = NavalCommand::Orders::Api;
static_assert(std::is_same_v<World::Eligibility, Orders::Eligibility>);
static_assert(std::is_aggregate_v<World::Unit>);
static_assert(std::is_aggregate_v<World::View>);

int main()
{
	World::Unit unit{"unit", "Friendly", {61.96, -10.37, std::nullopt}, std::nullopt, 1.0, {{"waypoint", Orders::Availability::Executable, "", "degrees"}}};
	World::Track track{"track", {61.0, -10.0, std::nullopt}, 1.0, "observer"};
	World::Facility facility{"facility", {{"class", "squadron", 2}}, 0, 1.0};
	World::View view{"session", "observer", true, false, 7, 1.0, {unit}, {track}, {facility}};
	return view.units.front().orders.front().availability == Orders::Availability::Executable && !view.units.front().position.altitudeMeters &&
	       view.facilities.front().stocks.front().unreservedCount == 2
		       ? 0
		       : 1;
}
