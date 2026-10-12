#include <NavalCommand/Physics/Api/MetersPerSecond.h>
#include <NavalCommand/Physics/Api/Position.h>
#include <NavalCommand/Physics/Api/Radians.h>
#include <NavalCommand/Physics/Api/Seconds.h>
#include <type_traits>

namespace Physics = NavalCommand::Physics::Api;

static_assert(!std::is_convertible_v<Physics::Meters, Physics::Seconds>);
static_assert(!std::is_convertible_v<Physics::Degrees, Physics::Radians>);
static_assert(!std::is_assignable_v<Physics::MetersPerSecond&, double>);

int main()
{
	const Physics::Position position{{61.96}, {-10.37}, {0}};
	return position.Latitude.Value == 61.96 && position.Longitude.Value == -10.37 &&
		position.Elevation.Value == 0 ? 0 : 1;
}
