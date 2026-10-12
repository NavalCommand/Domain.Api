#pragma once
#include <vector>
#include <NavalCommand/Equipment/Api/TypeId.h>
#include <NavalCommand/Resources/Api/Id.h>
#include <NavalCommand/Resources/Api/Value.h>
#include <optional>

namespace NavalCommand::Equipment::Api
{
	struct Fit
	{
		struct ResourceProvision
		{
			Resources::Api::Id ResourceId;
			Resources::Api::Value Capacity;
			// Initially loaded inventory may be smaller than theoretical capacity.
			Resources::Api::Value InitialInventory;
		};

		TypeId TypeId;
		// Absence means this fit has no resource capacity or initial inventory.
		std::optional<ResourceProvision> Resource;
	};
}
