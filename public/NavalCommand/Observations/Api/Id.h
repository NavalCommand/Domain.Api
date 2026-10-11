#pragma once
#include <string>

namespace NavalCommand::Observations::Api
{
	// Identifies an observer-side representation, not a truth entity; contacts may be false or fused.
	struct Id
	{
		std::string Value;
		bool operator==(const Id&) const = default;
	};
}
