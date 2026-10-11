#pragma once
#include <NavalCommand/Physics/Api/Seconds.h>
#include <NavalCommand/Uncertainty/Api/Knowledge.h>
#include <NavalCommand/Uncertainty/Api/ObservedCollection.h>
#include <NavalCommand/Units/Api/AircraftInventoryEntry.h>
#include <cstdint>

namespace NavalCommand::Units::Api
{
	struct AirOperations
	{
		Uncertainty::Api::ObservedCollection<AircraftInventoryEntry> Inventory;
		Uncertainty::Api::Knowledge<std::uint32_t> PendingOperations;
		Uncertainty::Api::Knowledge<std::uint32_t> OnboardCount;
		Uncertainty::Api::Knowledge<std::uint32_t> ReservedCount;
		Uncertainty::Api::Knowledge<std::uint32_t> CooldownCount;
		// Actual inventory observation time; independent of cached contact measurement time.
		Uncertainty::Api::Knowledge<Physics::Api::Seconds> MeasuredAt;
	};
}
