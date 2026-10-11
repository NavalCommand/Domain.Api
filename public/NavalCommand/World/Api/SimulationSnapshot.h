#pragma once
#include <NavalCommand/Physics/Api/Seconds.h>
#include <NavalCommand/Units/Api/UnitInstance.h>
#include <NavalCommand/World/Api/SimulationUnitMembership.h>
#include <string>
#include <vector>

namespace NavalCommand::World::Api
{
	struct SimulationSnapshot
	{
		std::string SessionId;
		Physics::Api::Seconds CapturedAt;
		std::vector<Units::Api::UnitInstance> Units;
		std::vector<SimulationUnitMembership> Memberships;
	};
}
