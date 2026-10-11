#pragma once
#include <NavalCommand/Catalog/Api/EquipmentFit.h>
#include <NavalCommand/Catalog/Api/LoadoutId.h>
#include <vector>

namespace NavalCommand::Catalog::Api
{
	struct Loadout
	{
		LoadoutId Id;
		std::vector<EquipmentFit> Equipment;
	};
}
