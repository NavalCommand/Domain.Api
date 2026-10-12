#pragma once

#include <NavalCommand/Equipment/Api/OperationalState.h>
#include <NavalCommand/Equipment/Api/Damage.h>
#include <NavalCommand/Equipment/Api/TypeId.h>
#include <NavalCommand/Resources/Api/Id.h>
#include <NavalCommand/Resources/Api/Value.h>

namespace NavalCommand::Equipment::Api
{
	struct Instance
	{
		TypeId Type;
		OperationalState OperationalReadiness;
		Damage DamageState;
		Resources::Api::Id ExpendableResourceId;
		Resources::Api::Value ExpendableResourceValue;
	};
}
