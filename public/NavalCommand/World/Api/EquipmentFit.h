#pragma once
#include <NavalCommand/World/Api/PhysicalTraits.h>
#include <NavalCommand/World/Api/ResourceQuantity.h>
#include <optional>
#include <string>
#include <vector>

namespace NavalCommand::World::Api {
struct EquipmentFit {
	std::string EquipmentTypeId;
	std::vector<ResourceQuantity> NominalResources;
	std::optional<PhysicalTraits> Physical;
};
}
