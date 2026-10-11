#pragma once
#include <NavalCommand/World/Api/Knowledge.h>
#include <string>

namespace NavalCommand::World::Api
{
	struct ObservationMetadata
	{
		Knowledge<double> SampledAtSeconds;
		Knowledge<std::string> Provenance;
	};
}
