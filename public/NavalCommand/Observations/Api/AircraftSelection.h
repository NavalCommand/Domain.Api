#pragma once
#include <NavalCommand/Catalog/Api/LoadoutId.h>
#include <NavalCommand/Catalog/Api/UnitTypeId.h>
#include <string>

namespace NavalCommand::Observations::Api
{
	// A selector reported by one observer's air-operations inventory, not a truth or permission token.
	struct AircraftSelection
	{
		Catalog::Api::UnitTypeId Type;
		std::string Squadron;
		Catalog::Api::LoadoutId Loadout;
	};
}
