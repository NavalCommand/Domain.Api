#pragma once
#include <cstdint>
#include <string>

namespace NavalCommand::Orders::Api {
struct FacilityLaunch {
	std::string classKey;
	std::string squadron;
	std::string loadout;
	std::uint32_t count{};
};
} // namespace NavalCommand::Orders::Api
