#pragma once
#include <NavalCommand/Catalog/Api/UnitTypeId.h>
#include <NavalCommand/Uncertainty/Api/Knowledge.h>
#include <string>

namespace NavalCommand::Units::Api
{
	struct IdentityState
	{
		Uncertainty::Api::Knowledge<std::string> Name;
		Uncertainty::Api::Knowledge<Catalog::Api::UnitTypeId> TypeId;
	};
}
