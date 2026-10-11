#pragma once
#include <NavalCommand/World/Api/Facility.h>
#include <NavalCommand/World/Api/UnitInstance.h>
#include <cstdint>
#include <string>
#include <vector>

namespace NavalCommand::World::Api
{
	struct View
	{
		std::string sessionId;
		std::string observerId;
		bool ready{};
		bool truncated{};
		std::uint64_t version{};
		double operationalSeconds{};
		std::vector<UnitInstance> Instances;
		std::vector<Facility> facilities;
	};
}
