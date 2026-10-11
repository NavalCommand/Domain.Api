#pragma once
#include <NavalCommand/World/Api/AircraftState.h>
#include <NavalCommand/World/Api/EquipmentInstance.h>
#include <NavalCommand/World/Api/IdentityState.h>
#include <NavalCommand/World/Api/KinematicsState.h>
#include <NavalCommand/World/Api/NavigationState.h>
#include <NavalCommand/World/Api/ObservationMetadata.h>
#include <NavalCommand/World/Api/OrderEligibilityState.h>
#include <NavalCommand/World/Api/Subject.h>
#include <optional>

namespace NavalCommand::World::Api
{
	struct UnitInstance
	{
		Subject Identity;
		IdentityState Display;
		KinematicsState Kinematics;
		ObservationMetadata Observation;
		ObservedCollection<EquipmentInstance> Equipment;
		std::optional<NavigationState> Navigation;
		std::optional<OrderEligibilityState> OrderEligibility;
		std::optional<AircraftState> Aircraft;
	};
}
