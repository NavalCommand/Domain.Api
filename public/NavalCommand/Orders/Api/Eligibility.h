#pragma once
#include <NavalCommand/Orders/Api/Availability.h>
#include <NavalCommand/Orders/Api/FacilityLaunch.h>
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
		// A launch selector is discovery context, not inventory and not dispatch authorization.
		std::optional<FacilityLaunch> LaunchOption;
	};
}
