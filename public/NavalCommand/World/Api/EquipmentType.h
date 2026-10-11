#pragma once
#include <NavalCommand/World/Api/EquipmentCapability.h>
#include <NavalCommand/World/Api/EquipmentOperation.h>
#include <NavalCommand/World/Api/PhysicalTraits.h>
#include <optional>
#include <string>
#include <vector>

namespace NavalCommand::World::Api
{
	struct EquipmentType
	{
		std::string Id;
		std::vector<EquipmentCapability> Capabilities;
		std::vector<EquipmentOperation> Operations;
		std::optional<PhysicalTraits> Physical;
	};
}
