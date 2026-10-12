#pragma once
#include <vector>
#include <NavalCommand/Equipment/Api/TypeId.h>
#include <NavalCommand/Resources/Api/Id.h>
#include <NavalCommand/Resources/Api/Value.h>

namespace NavalCommand::Equipment::Api
{
	struct Fit
	{
		TypeId TypeId;
		Resources::Api::Id ResourceId;
		Resources::Api::Value ResourceCapacity;
		// Initially loaded inventory may be smaller than theoretical capacity.
		Resources::Api::Value InitialInventory;
	};
}
