#pragma once
#include <NavalCommand/Catalog/Api/LoadoutId.h>
#include <NavalCommand/Catalog/Api/UnitTypeId.h>
#include <NavalCommand/Physics/Api/Seconds.h>
#include <NavalCommand/Uncertainty/Api/Exact.h>
#include <cstdint>
#include <string>
#include <vector>

namespace NavalCommand::Observations::Api
{
	struct AirOperationsObservation
	{
		// Stock is grouped by aircraft type and squadron; loadouts are reported choices, not duplicated stock.
		struct AircraftInventoryEntry
		{
			Uncertainty::Api::Exact<Catalog::Api::UnitTypeId> Type;
			Uncertainty::Api::Exact<std::string> Squadron;
			Uncertainty::Api::Exact<std::uint32_t> UnreservedCount;
			std::vector<Catalog::Api::LoadoutId> Loadouts;
		};

		// Rows and loadouts are only currently reported items, not an exhaustive inventory.
		std::vector<AircraftInventoryEntry> Inventory;
		Uncertainty::Api::Exact<std::uint32_t> PendingOperations;
		Uncertainty::Api::Exact<std::uint32_t> OnboardCount;
		Uncertainty::Api::Exact<std::uint32_t> ReservedCount;
		Uncertainty::Api::Exact<std::uint32_t> CooldownCount;
		Uncertainty::Api::Exact<Physics::Api::Seconds> MeasuredAt;
	};
}
