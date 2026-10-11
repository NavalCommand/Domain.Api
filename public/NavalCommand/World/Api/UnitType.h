#pragma once
#include <NavalCommand/World/Api/Loadout.h>
#include <NavalCommand/World/Api/PlatformDescription.h>
#include <string>
#include <vector>

namespace NavalCommand::World::Api {
struct UnitType {
	std::string Id;
	PlatformDescription Platform;
	std::vector<Loadout> Loadouts;
};
}
