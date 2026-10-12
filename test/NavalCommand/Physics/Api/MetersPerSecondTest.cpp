#include <NavalCommand/Physics/Api/MetersPerSecond.h>
#include <type_traits>

namespace Physics = NavalCommand::Physics::Api;

static_assert(!std::is_assignable_v<Physics::MetersPerSecond&, double>);
