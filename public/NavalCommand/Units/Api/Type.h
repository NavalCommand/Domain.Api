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

		std::optional<std::string> DisplayName;

		// The sole authoritative classification; category and dimension are derived.
		Classification::Api::SubCategory UnitSubCategory;

		// Intrinsic platform roles that apply independently of the selected loadout.
		std::vector<Classification::Api::Role> PlatformRoles;

		std::vector<Equipment::Api::Loadout> Loadouts;
	};

	// Deduplicated union: platform roles first, then roles by loadout declaration order.
	inline std::vector<Classification::Api::Role> GetRoles(const Type& type)
	{
		std::vector<Classification::Api::Role> roles;
		const auto addUniqueRole = [&roles](Classification::Api::Role role)
		{
			if (std::find(roles.begin(), roles.end(), role) == roles.end())
			{
				roles.push_back(role);
			}
		};

		for (const auto platformRole : type.PlatformRoles)
		{
			addUniqueRole(platformRole);
		}

		for (const auto& loadout : type.Loadouts)
		{
			for (const auto loadoutRole : loadout.Roles)
			{
				addUniqueRole(loadoutRole);
			}
		}

		return roles;
	}
}
