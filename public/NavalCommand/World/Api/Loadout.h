#pragma once
#include <NavalCommand/World/Api/EquipmentFit.h>
#include <string>
#include <vector>

namespace NavalCommand::World::Api {
struct Loadout {
	std::string Id;
	std::vector<EquipmentFit> Equipment;
};
}
