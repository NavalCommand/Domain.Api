#pragma once
#include <NavalCommand/Catalog/Api/EquipmentTypeId.h>
#include <NavalCommand/Catalog/Api/ResourceId.h>
#include <NavalCommand/Catalog/Api/ResourceValue.h>
#include <optional>
#include <vector>

namespace NavalCommand::Units::Api
{
	struct EquipmentInstance
	{
		enum class Readiness { Ready, Busy, Unavailable };
		enum class Damage { Intact, Damaged, Destroyed };

		struct Resource
		{
			Catalog::Api::ResourceId Id;
			Catalog::Api::ResourceValue Amount;
		};

		Catalog::Api::EquipmentTypeId Type;
		std::optional<bool> Active;
		std::optional<Readiness> OperationalReadiness;
		std::optional<Damage> DamageState;
		std::optional<std::vector<Resource>> Resources;
	};
}
