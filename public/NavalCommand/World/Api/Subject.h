#pragma once
#include <NavalCommand/Orders/Api/OwnUnitId.h>
#include <NavalCommand/World/Api/TrackId.h>
#include <variant>

namespace NavalCommand::World::Api
{
	// TODO Why OwnUnitId belongs to Orders::Api and is used by World::Api::UnitInstance as a primary key?
	// Also we probably need our own UnitId that does not depend on in-game ids.
	// This means that we don't have to split UnitId into OwnUnit and TackId.
	// From the client's perspective both own units and tacks are UnitInstances, so their Ids should also be uniform.
	using Subject = std::variant<std::monostate, Orders::Api::OwnUnitId, TrackId>;
}
