#pragma once
#include <NavalCommand/World/Api/Knowledge.h>
#include <string>

namespace NavalCommand::World::Api {
struct IdentityState {
	Knowledge<std::string> Name;
	Knowledge<std::string> TypeId;
};
}
