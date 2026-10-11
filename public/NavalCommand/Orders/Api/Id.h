#pragma once
#include <string>

namespace NavalCommand::Orders::Api
{
	struct Id
	{
		std::string Value;
		bool operator==(const Id&) const = default;
	};
}
