#pragma once
#include <NavalCommand/Orders/Api/Availability.h>
#include <NavalCommand/Orders/Api/LaunchAircraft.h>
#include <NavalCommand/Orders/Api/OrderKind.h>
#include <optional>
#include <string>

namespace NavalCommand::Orders::Api
{
	struct Eligibility
	{
		OrderKind Kind{};
		Orders::Api::Availability Availability{};
		std::string Reason;
		// Inventory selector context is not authorization to launch.
		std::optional<LaunchAircraft> LaunchOption;
	};
}
