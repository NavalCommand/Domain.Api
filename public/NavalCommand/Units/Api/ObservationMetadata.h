#pragma once
#include <NavalCommand/Physics/Api/Seconds.h>
#include <NavalCommand/Uncertainty/Api/Knowledge.h>

namespace NavalCommand::Units::Api
{
	struct ObservationMetadata
	{
		// Last actual measurement in session operational seconds, only when known.
		// Snapshot capture/cache export time must never populate a cached enemy measurement.
		Uncertainty::Api::Knowledge<Physics::Api::Seconds> MeasuredAt;
	};
}
