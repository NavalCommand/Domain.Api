#pragma once
#include <string>

namespace NavalCommand::Equipment::Api
{
	struct LoadoutId
	{
		std::string Value;
		bool operator==(const LoadoutId&) const = default;
	};
}
