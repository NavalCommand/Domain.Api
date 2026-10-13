#pragma once
#include <NavalCommand/Equipment/Api/Instance.h>
#include <NavalCommand/Equipment/Api/LoadoutId.h>
#include <NavalCommand/Factions/Api/Id.h>
#include <NavalCommand/Units/Api/AircraftInstance.h>
#include <NavalCommand/Units/Api/Id.h>
#include <NavalCommand/Units/Api/Kinematics.h>
#include <NavalCommand/Units/Api/TypeId.h>
#include <optional>
#include <string>
#include <vector>

namespace NavalCommand::Units::Api
{
	struct Instance
	{
		Id Identity;
		std::string Name;
		TypeId Type;
		// Selected loadout, if assigned/applicable.
		Equipment::Api::LoadoutId CurrentLoadout;
		Factions::Api::Id Faction;
		Kinematics Kinematics;
		std::vector<Equipment::Api::Instance> Equipment;
		std::optional<AircraftInstance> Aircraft;
	};
}
