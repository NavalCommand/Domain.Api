#pragma once
#include <NavalCommand/Units/Api/UnitId.h>
#include <NavalCommand/World/Api/FactionId.h>
#include <NavalCommand/World/Api/TaskForceId.h>

namespace NavalCommand::World::Api
{
	struct SimulationUnitMembership
	{
		Units::Api::UnitId Unit;
		FactionId Faction;
		TaskForceId TaskForce;
	};
}
