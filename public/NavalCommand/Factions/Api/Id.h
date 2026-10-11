#pragma once
#include <string>

namespace NavalCommand::Factions::Api
{
	struct Id
	{
		std::string Value;
		bool operator==(const Id&) const = default;
	};
}
