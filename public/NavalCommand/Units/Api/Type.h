#pragma once

#include <NavalCommand/Classification/Api/Role.h>
#include <NavalCommand/Classification/Api/SubCategory.h>
#include <NavalCommand/Equipment/Api/Loadout.h>
#include <NavalCommand/Units/Api/TypeId.h>
#include <algorithm>
#include <vector>

namespace NavalCommand::Units::Api
{
	struct Type
	{
		TypeId Id;

		// The sole authoritative classification; category and dimension are derived.
		Classification::Api::SubCategory UnitSubCategory;

		std::vector<Equipment::Api::Loadout> Loadouts;
	};

	// Deduplicated union of configured roles. Examine individual loadouts for partial knowledge.
	inline std::vector<Classification::Api::Role> GetRoles(const Type& type)
	{
		if (type.Loadouts.empty())
		{
			return {};
		}

		std::vector<Classification::Api::Role> roles;
		for (const auto& loadout : type.Loadouts)
		{
			for (const auto role : loadout.Roles)
			{
				if (std::find(roles.begin(), roles.end(), role) == roles.end())
				{
					roles.push_back(role);
				}
			}
		}

		return roles;
	}
}
