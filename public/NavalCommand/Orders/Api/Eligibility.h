#pragma once
#include <NavalCommand/Orders/Api/Availability.h>
#include <string>

namespace NavalCommand::Orders::Api
{
	struct Eligibility
	{
		// TODO Public fields must be CamelCase, e.g. Kind, not kind.
		std::string kind;
		Availability availability{};
		std::string reason;
		std::string arguments;
	};
} // namespace NavalCommand::Orders::Api
