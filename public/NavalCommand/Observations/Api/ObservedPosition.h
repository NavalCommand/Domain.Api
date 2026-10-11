#pragma once
#include <NavalCommand/Observations/Api/PartiallyLocalizedPosition.h>
#include <NavalCommand/Physics/Api/Position.h>
#include <NavalCommand/Uncertainty/Api/Exact.h>
#include <variant>

namespace NavalCommand::Observations::Api
{
	using ObservedPosition = std::variant<
		Uncertainty::Api::Exact<Physics::Api::Position>,
		PartiallyLocalizedPosition>;
}
