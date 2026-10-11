#pragma once
#include <NavalCommand/Uncertainty/Api/Exact.h>

namespace NavalCommand::Observations::Api
{
	struct Aircraft
	{
		Uncertainty::Api::Exact<bool> Airborne;
	};
}
