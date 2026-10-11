#pragma once
#include <NavalCommand/Physics/Api/Seconds.h>
#include <NavalCommand/Units/Api/AircraftInventoryEntry.h>
#include <cstdint>
#include <optional>
#include <vector>

namespace NavalCommand::Units::Api
{
	struct AirOperations
	{
		std::optional<std::vector<AircraftInventoryEntry>> Inventory;
		std::optional<std::uint32_t> PendingOperations;
		std::optional<std::uint32_t> OnboardCount;
		std::optional<std::uint32_t> ReservedCount;
		std::optional<std::uint32_t> CooldownCount;
		std::optional<Physics::Api::Seconds> SampledAt;
	};
}
