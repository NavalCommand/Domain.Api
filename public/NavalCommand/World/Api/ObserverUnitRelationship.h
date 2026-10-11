#pragma once
#include <NavalCommand/Observations/Api/ObservationId.h>
#include <NavalCommand/Uncertainty/Api/Exact.h>
#include <NavalCommand/World/Api/FactionId.h>
#include <NavalCommand/World/Api/TaskForceId.h>

namespace NavalCommand::World::Api
{
	struct ObserverUnitRelationship
	{
		Observations::Api::ObservationId Observation;
		Uncertainty::Api::Exact<FactionId> Faction;
		Uncertainty::Api::Exact<TaskForceId> TaskForce;
	};
}
