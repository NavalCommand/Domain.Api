#pragma once
#include <NavalCommand/World/Api/Knowledge.h>

namespace NavalCommand::World::Api {
struct AircraftState {
	Knowledge<bool> Airborne;
};
}
