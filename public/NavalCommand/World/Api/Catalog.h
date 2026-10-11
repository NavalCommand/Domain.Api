#pragma once
#include <NavalCommand/World/Api/EquipmentType.h>
#include <NavalCommand/World/Api/UnitType.h>
#include <string>
#include <vector>

namespace NavalCommand::World::Api {
// Definitive definitions for one resolved context; no observation uncertainty.
struct Catalog {
	std::string Revision;
	std::vector<UnitType> UnitTypes;
	std::vector<EquipmentType> EquipmentTypes;
};
}
