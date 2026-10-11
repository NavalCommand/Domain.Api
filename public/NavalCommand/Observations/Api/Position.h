#pragma once
#include <NavalCommand/Observations/Api/PartiallyLocalizedPosition.h>
#include <NavalCommand/Physics/Api/Position.h>
#include <variant>

namespace NavalCommand::Observations::Api
{
	using Position = std::variant<
		Physics::Api::Position,
		PartiallyLocalizedPosition>;
}
