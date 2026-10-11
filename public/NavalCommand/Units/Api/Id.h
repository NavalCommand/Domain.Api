#pragma once
#include <string>

namespace NavalCommand::Units::Api
{
	// Authoritative simulated tactical entity identity; adapters own native-ID mappings.
	struct Id
	{
		std::string Value;
		bool operator==(const Id&) const = default;
	};
}
