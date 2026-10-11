#pragma once
#include <NavalCommand/Physics/Api/Seconds.h>
#include <NavalCommand/Uncertainty/Api/ObservedCollection.h>
#include <NavalCommand/Units/Api/UnitInstance.h>
#include <NavalCommand/World/Api/UnitMembership.h>
#include <cstdint>
#include <string>
#include <vector>

namespace NavalCommand::World::Api
{
	struct View
	{
		std::string SessionId;
		std::string ObserverId;
		bool Ready{};
		bool Truncated{};
		std::uint64_t Version{};
		// Snapshot capture in session operational seconds, not a sensor measurement timestamp.
		Physics::Api::Seconds CapturedAt;
		std::vector<Units::Api::UnitInstance> Instances;
		Uncertainty::Api::ObservedCollection<UnitMembership> Memberships;
	};
}
