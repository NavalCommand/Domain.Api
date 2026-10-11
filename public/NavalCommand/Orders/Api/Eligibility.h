#pragma once
#include <NavalCommand/Orders/Api/Availability.h>
#include <string>

namespace NavalCommand::Orders::Api
{
	struct Eligibility
	{
		// TODO Public fields must be CamelCase, e.g. Kind, not kind.
		// TODO What is Kind? Its type is string, which tells nothing about what this field stores.
		std::string kind;
		Availability availability{};
		std::string reason;
		std::string arguments;
	};
} // namespace NavalCommand::Orders::Api
