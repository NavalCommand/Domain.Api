#pragma once
#include <string>

namespace NavalCommand::Units::Api
{
	// Observer/session-scoped observation handle. Does not imply a real platform or command authority.
	struct UnitId
	{
		std::string Value;
		bool operator==(const UnitId&) const = default;
	};
}
