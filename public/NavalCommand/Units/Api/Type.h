#pragma once

#include <NavalCommand/Classification/Api/Category.h>
#include <NavalCommand/Equipment/Api/Loadout.h>
#include <NavalCommand/Units/Api/TypeId.h>
#include <vector>

namespace NavalCommand::Units::Api
{
	struct Type
	{
		TypeId Id;
		Category UnitClassification;
		std::vector<Equipment::Api::Loadout> Loadouts;
	};
}
