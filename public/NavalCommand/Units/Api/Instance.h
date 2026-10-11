#pragma once
#include <NavalCommand/Units/Api/Id.h>
#include <NavalCommand/Units/Api/TypeId.h>
#include <NavalCommand/Units/Api/Navigation.h>
#include <NavalCommand/Units/Api/AircraftInstance.h>
#include <NavalCommand/Units/Api/AirOperations.h>
#include <NavalCommand/Units/Api/Kinematics.h>
#include <optional>
#include <vector>
#include <NavalCommand/Equipment/Api/Instance.h>
#include <NavalCommand/Units/Api/Activity.h>
#include <NavalCommand/Factions/Api/Id.h>

namespace NavalCommand::Units::Api
{
	struct Instance
	{
		Id Identity;
		std::string Name;
		TypeId Type;
		Factions::Api::Id Faction;
		Kinematics Kinematics;
		std::vector<Equipment::Api::Instance> Equipment;
		std::optional<Navigation> Navigation;
		std::optional<AircraftInstance> Aircraft;
		std::optional<AirOperations> AirOperations;
		Activity CurrentActivity;
	};
}
