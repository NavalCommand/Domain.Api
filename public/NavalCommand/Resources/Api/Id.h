#pragma once
#include <string>

namespace NavalCommand::Resources::Api
{
	struct Id
	{
		std::string Value;
		bool operator==(const Id&) const = default;
	};
}
