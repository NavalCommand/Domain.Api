#pragma once
#include <NavalCommand/Observations/Api/Aircraft.h>
#include <NavalCommand/Observations/Api/Contributor.h>
#include <NavalCommand/Observations/Api/Id.h>
#include <NavalCommand/Observations/Api/Kinematics.h>
#include <NavalCommand/Physics/Api/Seconds.h>
#include <NavalCommand/Uncertainty/Api/Exact.h>
#include <NavalCommand/Units/Api/TypeId.h>
#include <optional>
#include <string>
#include <vector>
#include <NavalCommand/Factions/Api/Id.h>

namespace NavalCommand::Observations::Api
{
	struct Instance
	{
		Id Identity;
		std::string ObservationName; // Observer-facing name. Can be a track name or real unit name
		Factions::Api::Id ObserverFaction;
		Uncertainty::Api::Exact<Factions::Api::Id> ObservationFaction;
		Uncertainty::Api::Exact<Units::Api::TypeId> Type;
		Kinematics Kinematics;
		std::optional<Aircraft> Aircraft;

		// Only source-supported attribution; empty means no contributors reported.
		std::vector<Contributor> Contributors;
		Uncertainty::Api::Exact<Physics::Api::Seconds> MeasuredAt;
	};
}
