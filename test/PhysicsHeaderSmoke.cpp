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
	Physics::Position seaLevel{{61.96}, {-10.37}, Physics::Meters{0}};
	Physics::Position unknownAltitude{{61.96}, {-10.37}, std::nullopt};
	return seaLevel.Altitude->Value == 0 && !unknownAltitude.Altitude && seaLevel.Latitude.Value == 61.96 ? 0 : 1;
}
