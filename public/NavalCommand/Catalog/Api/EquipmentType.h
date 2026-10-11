#pragma once
#include <NavalCommand/Catalog/Api/EquipmentEffect.h>
#include <NavalCommand/Catalog/Api/EquipmentOperation.h>
#include <NavalCommand/Catalog/Api/EquipmentTypeId.h>
#include <vector>

namespace NavalCommand::Catalog::Api
{
	// One independently addressable operational capability, not necessarily one physical device.
	struct EquipmentType
	{
		EquipmentTypeId Id;
		std::vector<EquipmentEffect> Effects;
		std::vector<EquipmentOperation> Operations;
	};
}
