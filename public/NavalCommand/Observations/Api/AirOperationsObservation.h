#pragma once
#include <NavalCommand/Catalog/Api/LoadoutId.h>
#include <NavalCommand/Catalog/Api/UnitTypeId.h>
#include <NavalCommand/Physics/Api/Seconds.h>
#include <NavalCommand/Uncertainty/Api/Knowledge.h>
#include <NavalCommand/Uncertainty/Api/ObservedCollection.h>
#include <cstdint>
#include <string>
#include <vector>

namespace NavalCommand::Observations::Api
{
	struct AirOperationsObservation
	{
		// Stock is grouped by aircraft type and squadron; loadouts describe choices, not separate stock.
		struct AircraftInventoryEntry
		{
			Uncertainty::Api::Knowledge<Catalog::Api::UnitTypeId> Type;
			Uncertainty::Api::Knowledge<std::string> Squadron;
			Uncertainty::Api::Knowledge<std::uint32_t> UnreservedCount;
			Uncertainty::Api::ObservedCollection<Catalog::Api::LoadoutId> Loadouts;
		};

		Uncertainty::Api::ObservedCollection<AircraftInventoryEntry> Inventory;
		Uncertainty::Api::Knowledge<std::uint32_t> PendingOperations;
		Uncertainty::Api::Knowledge<std::uint32_t> OnboardCount;
		Uncertainty::Api::Knowledge<std::uint32_t> ReservedCount;
		Uncertainty::Api::Knowledge<std::uint32_t> CooldownCount;
		Uncertainty::Api::Knowledge<Physics::Api::Seconds> MeasuredAt;
	};
}
