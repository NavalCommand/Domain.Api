#pragma once

#include <vector>
#include <NavalCommand/Equipment/Api/Loadout.h>
#include <NavalCommand/Units/Api/Classification.h>
#include <NavalCommand/Units/Api/TypeId.h>

namespace NavalCommand::Units::Api
{
	struct Type
	{
		TypeId Id;
		Classification UnitClassification;
		std::vector<Equipment::Api::Loadout> Loadouts;
	};
}
