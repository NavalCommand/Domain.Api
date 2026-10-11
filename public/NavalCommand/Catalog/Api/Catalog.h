#pragma once
#include <NavalCommand/Catalog/Api/EquipmentType.h>
#include <NavalCommand/Catalog/Api/ResourceDefinition.h>
#include <NavalCommand/Catalog/Api/UnitType.h>
#include <string>
#include <vector>

namespace NavalCommand::Catalog::Api
{
	// Authoritative definitions resolved for one session/content context. No observer uncertainty.
	struct Catalog
	{
		std::string Revision;
		std::vector<UnitType> UnitTypes;
		std::vector<EquipmentType> EquipmentTypes;
		std::vector<ResourceDefinition> Resources;
	};
}
