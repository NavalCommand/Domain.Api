#pragma once
#include <NavalCommand/World/Api/Knowledge.h>
#include <string>

namespace NavalCommand::World::Api
{
	struct ObservationMetadata
	{
		Knowledge<double> SampledAtSeconds; // TODO Does this field encode when the API query was made or when a simulated sensor acquired Unit's track?
		Knowledge<std::string> Provenance; // TODO Too vague. This should probably point to sensor that is tracking the unit.
	};
}
