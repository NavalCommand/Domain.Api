#pragma once
#include <string>

namespace NavalCommand::Observations::Api
{
	// Identifies an observer-side representation, not a truth entity; contacts may be false or fused.
	struct ObservationId
	{
		std::string Value;
		bool operator==(const ObservationId&) const = default;
	};
}
