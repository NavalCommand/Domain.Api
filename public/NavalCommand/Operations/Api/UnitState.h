#pragma once
#include <NavalCommand/Operations/Api/Activity.h>
#include <NavalCommand/Operations/Api/AirOperations.h>
#include <NavalCommand/Operations/Api/Navigation.h>
#include <optional>

namespace NavalCommand::Operations::Api
{
	struct UnitState
	{
		Activity CurrentActivity;
		std::optional<Navigation> NavigationState;
		std::optional<AirOperations> AirOperationsState;
	};
}
