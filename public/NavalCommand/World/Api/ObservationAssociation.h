#pragma once
#include <NavalCommand/Observations/Api/ObservationId.h>
#include <NavalCommand/Observations/Api/ObserverId.h>
#include <NavalCommand/Units/Api/UnitId.h>

namespace NavalCommand::World::Api
{
	// Privileged-only label; vectors in recorded sessions permit absent and many-to-many links.
	struct ObservationAssociation
	{
		Observations::Api::ObserverId Observer;
		Observations::Api::ObservationId Observation;
		Units::Api::UnitId Unit;
	};
}
