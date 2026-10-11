#pragma once
#include <NavalCommand/Catalog/Api/UnitTypeId.h>
#include <NavalCommand/Observations/Api/AircraftObservation.h>
#include <NavalCommand/Observations/Api/AirOperationsObservation.h>
#include <NavalCommand/Observations/Api/EquipmentObservation.h>
#include <NavalCommand/Observations/Api/NavigationObservation.h>
#include <NavalCommand/Observations/Api/ObservationId.h>
#include <NavalCommand/Observations/Api/ObservationMetadata.h>
#include <NavalCommand/Observations/Api/ObservedKinematics.h>
#include <NavalCommand/Uncertainty/Api/Knowledge.h>
#include <NavalCommand/Uncertainty/Api/ObservedCollection.h>
#include <optional>
#include <string>

namespace NavalCommand::Observations::Api
{
	struct UnitObservation
	{
		ObservationId Identity;
		Uncertainty::Api::Knowledge<std::string> Name;
		Uncertainty::Api::Knowledge<Catalog::Api::UnitTypeId> Type;
		ObservedKinematics Kinematics;
		Uncertainty::Api::ObservedCollection<EquipmentObservation> Equipment;
		std::optional<NavigationObservation> Navigation;
		std::optional<AircraftObservation> Aircraft;
		std::optional<AirOperationsObservation> AirOperations;
		ObservationMetadata Evidence;
	};
}
