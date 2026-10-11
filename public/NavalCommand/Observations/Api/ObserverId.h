#pragma once
#include <string>

namespace NavalCommand::Observations::Api
{
	struct ObserverId
	{
		std::string Value;
		bool operator==(const ObserverId&) const = default;
	};
}
