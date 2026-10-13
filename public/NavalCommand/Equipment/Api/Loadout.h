#pragma once

#include <NavalCommand/Classification/Api/Role.h>
#include <NavalCommand/Equipment/Api/Fit.h>
#include <NavalCommand/Equipment/Api/LoadoutId.h>
#include <optional>
#include <vector>

namespace NavalCommand::Equipment::Api
{
	struct Loadout
	{
		LoadoutId Id;
		std::vector<Fit> Equipment;

		// Roles supported by this configuration, not its current orders.
		// nullopt = unreported; an empty vector = known to have no roles.
		std::optional<std::vector<Classification::Api::Role>> Roles;
	};
}
