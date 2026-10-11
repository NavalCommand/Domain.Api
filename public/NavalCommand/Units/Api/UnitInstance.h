#pragma once
#include <NavalCommand/Units/Api/UnitId.h>
#include <NavalCommand/Catalog/Api/UnitTypeId.h>
#include <NavalCommand/Units/Api/NavigationState.h>
#include <NavalCommand/Units/Api/AircraftState.h>
#include <NavalCommand/Units/Api/AirOperations.h>
#include <NavalCommand/Units/Api/EquipmentInstance.h>
#include <NavalCommand/Units/Api/KinematicsState.h>
#include <optional>
#include <vector>

namespace NavalCommand::Units::Api
{
	struct UnitInstance
	{
		UnitId Identity;
		std::optional<Catalog::Api::UnitTypeId> Type;
		KinematicsState Kinematics;
		std::optional<std::vector<EquipmentInstance>> Equipment;
		std::optional<NavigationState> Navigation;
		std::optional<AircraftState> Aircraft;
		std::optional<AirOperations> AirOperations;
	};
}
