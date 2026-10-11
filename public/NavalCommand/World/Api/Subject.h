#pragma once
#include <NavalCommand/Orders/Api/OwnUnitId.h>
#include <NavalCommand/World/Api/TrackId.h>
#include <variant>

namespace NavalCommand::World::Api {
using Subject = std::variant<std::monostate, Orders::Api::OwnUnitId, TrackId>;
}
