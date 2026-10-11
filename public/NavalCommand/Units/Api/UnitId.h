#pragma once
#include <string>

namespace NavalCommand::Units::Api
{
	// Authoritative simulated tactical entity identity; adapters own native-ID mappings.
	struct UnitId
	{
		std::string Value;
		bool operator==(const UnitId&) const = default;
	};
}
