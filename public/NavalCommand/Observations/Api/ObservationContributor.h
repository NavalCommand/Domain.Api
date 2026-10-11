#pragma once
#include <NavalCommand/Catalog/Api/EquipmentTypeId.h>
#include <NavalCommand/Observations/Api/ObservationId.h>
#include <vector>

namespace NavalCommand::Observations::Api
{
	struct ObservationContributor
	{
		ObservationId Observer;
		std::vector<Catalog::Api::EquipmentTypeId> Sensors;
	};
}
