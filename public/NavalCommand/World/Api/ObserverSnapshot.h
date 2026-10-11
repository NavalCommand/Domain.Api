#pragma once
#include <NavalCommand/Observations/Api/ObserverId.h>
#include <NavalCommand/Observations/Api/UnitObservation.h>
#include <NavalCommand/Physics/Api/Seconds.h>
#include <NavalCommand/World/Api/ObserverUnitRelationship.h>
#include <cstdint>
#include <string>
#include <vector>

namespace NavalCommand::World::Api
{
	struct ObserverSnapshot
	{
		std::string SessionId;
		Observations::Api::ObserverId Observer;
		bool Ready{};
		bool Truncated{};
		std::uint64_t Version{};
		Physics::Api::Seconds CapturedAt;
		std::vector<Observations::Api::UnitObservation> Units;
		std::vector<ObserverUnitRelationship> Memberships;
	};
}
