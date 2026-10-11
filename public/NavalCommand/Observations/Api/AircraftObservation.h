#pragma once
#include <NavalCommand/Uncertainty/Api/Exact.h>

namespace NavalCommand::Observations::Api
{
	struct AircraftObservation
	{
		Uncertainty::Api::Exact<bool> Airborne;
	};
}
