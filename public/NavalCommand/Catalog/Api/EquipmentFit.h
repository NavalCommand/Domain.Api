#pragma once
#include <NavalCommand/Catalog/Api/EquipmentTypeId.h>
#include <NavalCommand/Catalog/Api/ResourceQuantity.h>
#include <vector>

namespace NavalCommand::Catalog::Api
{
	struct EquipmentFit
	{
		EquipmentTypeId TypeId;
		std::vector<ResourceQuantity> Capacity;
		std::vector<ResourceQuantity> InitialInventory;
	};
}
