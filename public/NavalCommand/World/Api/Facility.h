#pragma once
#include <NavalCommand/World/Api/Stock.h>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace NavalCommand::World::Api {
struct Facility {
	std::string entityId;
	std::vector<Stock> stocks;
	std::uint32_t pendingOperations{};
	double sampledAtSeconds{};
	std::optional<std::uint32_t> onboardCount;
	std::optional<std::uint32_t> reservedCount;
	std::optional<std::uint32_t> cooldownCount;
};
} // namespace NavalCommand::World::Api
