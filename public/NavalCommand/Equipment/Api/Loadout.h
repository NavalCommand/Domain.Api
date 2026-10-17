#pragma once

#include <NavalCommand/Classification/Api/Role.h>
#include <NavalCommand/Equipment/Api/Fit.h>
#include <NavalCommand/Equipment/Api/LoadoutId.h>
#include <vector>

namespace NavalCommand::Equipment::Api
{
	struct Loadout
	{
		LoadoutId Id;
		std::optional<std::string> DisplayName;
		std::vector<Fit> Equipment;

		// Roles supported by this configuration, not its current orders.
		std::vector<Classification::Api::Role> Roles;
	};
}
