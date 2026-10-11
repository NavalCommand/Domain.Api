#pragma once
#include <NavalCommand/Equipment/Api/LoadoutId.h>
#include <vector>
#include <NavalCommand/Equipment/Api/Fit.h>

namespace NavalCommand::Equipment::Api
{
	struct Loadout
	{
		LoadoutId Id;
		std::vector<Fit> Equipment;
	};
}
