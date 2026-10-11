#pragma once
#include <NavalCommand/Units/Api/AirOperations.h>
#include <NavalCommand/Units/Api/AircraftState.h>
#include <NavalCommand/Units/Api/EquipmentInstance.h>
#include <NavalCommand/Units/Api/IdentityState.h>
#include <NavalCommand/Units/Api/KinematicsState.h>
#include <NavalCommand/Units/Api/NavigationState.h>
#include <NavalCommand/Units/Api/ObservationMetadata.h>
#include <NavalCommand/Units/Api/UnitId.h>
#include <optional>

namespace NavalCommand::Units::Api
{
	struct UnitInstance
	{
		UnitId Identity;
		IdentityState Display;
		KinematicsState Kinematics;
		ObservationMetadata Observation;
		Uncertainty::Api::ObservedCollection<EquipmentInstance> Equipment;
		std::optional<NavigationState> Navigation;
		std::optional<AircraftState> Aircraft;
		std::optional<Units::Api::AirOperations> AirOperations;
	};
}
