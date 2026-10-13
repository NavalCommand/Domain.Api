#pragma once

#include <NavalCommand/Classification/Api/Category.h>
#include <NavalCommand/Classification/Api/Role.h>
#include <NavalCommand/Classification/Api/SubCategory.h>
#include <NavalCommand/Equipment/Api/Loadout.h>
#include <NavalCommand/Units/Api/TypeId.h>
#include <algorithm>
#include <optional>
#include <vector>

namespace NavalCommand::Units::Api
{
	struct Type
	{
		TypeId Id;

		// Absent classification means the backend could not establish it.
		// If both are present, GetCategory(UnitSubCategory) must equal UnitCategory.
		std::optional<Classification::Api::Category> UnitCategory;
		std::optional<Classification::Api::SubCategory> UnitSubCategory;

		std::vector<Equipment::Api::Loadout> Loadouts;
	};

	// Deduplicated union of configured roles, or nullopt if any role data
	// is unavailable. Examine individual loadouts for partial knowledge.
	inline std::optional<std::vector<Classification::Api::Role>> GetRoles(const Type& type)
	{
		if (type.Loadouts.empty())
		{
			return std::nullopt;
		}

		std::vector<Classification::Api::Role> roles;
		for (const auto& loadout : type.Loadouts)
		{
			if (!loadout.Roles.has_value())
			{
				return std::nullopt;
			}

			for (const auto role : *loadout.Roles)
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
