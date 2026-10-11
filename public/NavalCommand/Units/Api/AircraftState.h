#pragma once
#include <NavalCommand/Uncertainty/Api/Knowledge.h>

namespace NavalCommand::Units::Api
{
	struct AircraftState
	{
		Uncertainty::Api::Knowledge<bool> Airborne;
	};
}
