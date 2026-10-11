#pragma once
#include <NavalCommand/Catalog/Api/EquipmentTypeId.h>
#include <NavalCommand/Catalog/Api/ResourceId.h>
#include <NavalCommand/Catalog/Api/ResourceValue.h>
#include <NavalCommand/Uncertainty/Api/Knowledge.h>
#include <NavalCommand/Uncertainty/Api/ObservedCollection.h>

namespace NavalCommand::Observations::Api
{
	struct EquipmentObservation
	{
		struct Resource
		{
			Catalog::Api::ResourceId Id;
			Uncertainty::Api::Knowledge<Catalog::Api::ResourceValue> Amount;
		};

		Uncertainty::Api::Knowledge<Catalog::Api::EquipmentTypeId> Type;
		Uncertainty::Api::Knowledge<bool> Active;
		Uncertainty::Api::ObservedCollection<Resource> Resources;
	};
}
