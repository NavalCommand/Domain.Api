#pragma once
#include <NavalCommand/Catalog/Api/EquipmentTypeId.h>
#include <NavalCommand/Catalog/Api/ResourceId.h>
#include <NavalCommand/Catalog/Api/ResourceValue.h>
#include <NavalCommand/Uncertainty/Api/Exact.h>
#include <vector>

namespace NavalCommand::Observations::Api
{
	struct EquipmentObservation
	{
		struct Resource
		{
			Catalog::Api::ResourceId Id;
			Uncertainty::Api::Exact<Catalog::Api::ResourceValue> Amount;
		};

		Uncertainty::Api::Exact<Catalog::Api::EquipmentTypeId> Type;
		Uncertainty::Api::Exact<bool> Active;
		std::vector<Resource> Resources;
	};
}
