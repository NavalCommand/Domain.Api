#pragma once
#include <NavalCommand/Catalog/Api/UnitTypeId.h>
#include <NavalCommand/Observations/Api/AircraftObservation.h>
#include <NavalCommand/Observations/Api/AirOperationsObservation.h>
#include <NavalCommand/Observations/Api/EquipmentObservation.h>
#include <NavalCommand/Observations/Api/NavigationObservation.h>
#include <NavalCommand/Observations/Api/ObservationContributor.h>
#include <NavalCommand/Observations/Api/ObservationId.h>
#include <NavalCommand/Observations/Api/ObservedKinematics.h>
#include <NavalCommand/Physics/Api/Seconds.h>
#include <NavalCommand/Uncertainty/Api/Exact.h>
#include <optional>
#include <string>
#include <vector>

namespace NavalCommand::Observations::Api
{
	struct UnitObservation
	{
		ObservationId Identity;
		Uncertainty::Api::Exact<std::string> Name;
		Uncertainty::Api::Exact<Catalog::Api::UnitTypeId> Type;
		ObservedKinematics Kinematics;
		// Only currently reported items; an empty list is not evidence of an exhaustive inventory.
		std::vector<EquipmentObservation> Equipment;
		std::optional<NavigationObservation> Navigation;
		std::optional<AircraftObservation> Aircraft;
		std::optional<AirOperationsObservation> AirOperations;
		// Only source-supported attribution; empty means no contributors reported.
		std::vector<ObservationContributor> Contributors;
		Uncertainty::Api::Exact<Physics::Api::Seconds> MeasuredAt;
	};
}
