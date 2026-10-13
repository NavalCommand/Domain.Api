#pragma once

#include <NavalCommand/Classification/Api/Category.h>
#include <NavalCommand/Classification/Api/Role.h>
#include <NavalCommand/Classification/Api/SubCategory.h>
#include <NavalCommand/Equipment/Api/Loadout.h>
#include <NavalCommand/Units/Api/TypeId.h>
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

		// Designed platform roles, not the current mission or equipped capabilities.
		// nullopt = unavailable; an empty vector = positively known to have no roles.
		std::optional<std::vector<Classification::Api::Role>> DesignedRoles;

		std::vector<Equipment::Api::Loadout> Loadouts;
	};
}
