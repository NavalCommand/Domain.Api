#pragma once
#include <NavalCommand/Uncertainty/Api/Knowledge.h>

namespace NavalCommand::Observations::Api
{
	struct AircraftObservation
	{
		Uncertainty::Api::Knowledge<bool> Airborne;
	};
}
