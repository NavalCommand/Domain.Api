#pragma once

#include <NavalCommand/Equipment/Api/OperationalState.h>
#include <NavalCommand/Equipment/Api/Damage.h>
#include <NavalCommand/Equipment/Api/TypeId.h>
#include <NavalCommand/Resources/Api/Id.h>
#include <NavalCommand/Resources/Api/Value.h>
#include <optional>

namespace NavalCommand::Equipment::Api
{
	struct Instance
	{
		struct ResourceInventory
		{
			Resources::Api::Id ResourceId;
			Resources::Api::Value Quantity;
		};

		TypeId Type;
		OperationalState State;
		Damage DamageState;
		// Absence means no resource inventory, not a depleted inventory.
		std::optional<ResourceInventory> Inventory;
	};
}
