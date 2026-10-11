#pragma once
#include <NavalCommand/Observations/Api/ObservationId.h>
#include <NavalCommand/Uncertainty/Api/Knowledge.h>
#include <NavalCommand/World/Api/FactionId.h>
#include <NavalCommand/World/Api/TaskForceId.h>

namespace NavalCommand::World::Api
{
	struct ObserverUnitRelationship
	{
		Observations::Api::ObservationId Observation;
		Uncertainty::Api::Knowledge<FactionId> Faction;
		Uncertainty::Api::Knowledge<TaskForceId> TaskForce;
	};
}
