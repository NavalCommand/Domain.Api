#pragma once
#include <NavalCommand/Orders/Api/Availability.h>
#include <cstdint>
#include <string>
#include <vector>

namespace NavalCommand::World::Api {
struct LaunchOption {
	std::string loadout;
	Orders::Api::Availability availability{};
	std::string reason;
};
struct Stock {
	std::string classKey;
	std::string squadron;
	std::uint32_t unreservedCount{};
	std::vector<LaunchOption> launchOptions;
};
} // namespace NavalCommand::World::Api
