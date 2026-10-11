#pragma once
#include <NavalCommand/Physics/Api/Seconds.h>
#include <optional>
#include <string>
#include <vector>

namespace NavalCommand::Observations::Api
{
	struct ObservationMetadata
	{
		std::optional<Physics::Api::Seconds> MeasuredAt;
		std::vector<std::string> Evidence;
	};
}
