#pragma once
#include <vector>
#include <NavalCommand/Equipment/Api/Instance.h>
#include <NavalCommand/Units/Api/Id.h>

namespace NavalCommand::Observations::Api
{
	struct Contributor
	{
		Units::Api::Id Observer;
		std::vector<Equipment::Api::TypeId> Sensors;
	};
}
