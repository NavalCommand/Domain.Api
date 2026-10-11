#pragma once
#include <NavalCommand/Catalog/Api/EquipmentTypeId.h>
#include <NavalCommand/Catalog/Api/ResourceId.h>
#include <NavalCommand/Catalog/Api/ResourceValue.h>
#include <NavalCommand/Uncertainty/Api/Knowledge.h>
#include <NavalCommand/Uncertainty/Api/ObservedCollection.h>

namespace NavalCommand::Units::Api
{
	struct EquipmentInstance
	{
		enum class Readiness
		{
			Ready,
			Busy,
			Unavailable
		};

		enum class Damage
		{
			Intact,
			Damaged,
			Destroyed
		};

		struct Resource
		{
			Catalog::Api::ResourceId Id;
			Uncertainty::Api::Knowledge<Catalog::Api::ResourceValue> Amount;
		};

		Uncertainty::Api::Knowledge<Catalog::Api::EquipmentTypeId> TypeId;
		Uncertainty::Api::Knowledge<bool> Active;
		Uncertainty::Api::Knowledge<Readiness> OperationalReadiness;
		Uncertainty::Api::Knowledge<Damage> DamageState;
		// Complete(empty) confirms resources are not applicable. Unknown does not.
		Uncertainty::Api::ObservedCollection<Resource> Resources;
	};
}
