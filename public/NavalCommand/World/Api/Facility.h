#pragma once
#include <NavalCommand/World/Api/Stock.h>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace NavalCommand::World::Api
{
	// TODO Unclear name. What facility? Should be Airbase or something like that.
	struct Facility
	{
		std::string entityId;
		std::vector<Stock> stocks;
		std::uint32_t pendingOperations{};
		double sampledAtSeconds{}; // TODO Sampling semantics leakage into Unit Component. Units already have ObservationMetadata.
		std::optional<std::uint32_t> onboardCount;
		std::optional<std::uint32_t> reservedCount;
		std::optional<std::uint32_t> cooldownCount;
	};
}
