#pragma once
#include <NavalCommand/Catalog/Api/Loadout.h>
#include <NavalCommand/Catalog/Api/PlatformDescription.h>
#include <NavalCommand/Catalog/Api/UnitTypeId.h>
#include <optional>
#include <vector>

namespace NavalCommand::Catalog::Api
{
	struct UnitType
	{
		UnitTypeId Id;
		std::optional<PlatformDescription> Platform;
		std::vector<Loadout> Loadouts;
	};
}
