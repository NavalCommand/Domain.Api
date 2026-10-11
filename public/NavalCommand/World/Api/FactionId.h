#pragma once
#include <string>

namespace NavalCommand::World::Api
{
	struct FactionId
	{
		std::string Value;
		bool operator==(const FactionId&) const = default;
	};
}
