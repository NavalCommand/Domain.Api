#pragma once
#include <NavalCommand/Orders/Api/Availability.h>
#include <cstdint>
#include <string>
#include <vector>

namespace NavalCommand::World::Api
{
	struct Stock
	{
		struct LaunchOption
		{
			std::string loadout;
			Orders::Api::Availability availability{};
			std::string reason;
		};

		std::string classKey;
		std::string squadron;
		std::uint32_t unreservedCount{};
		std::vector<LaunchOption> launchOptions;
	};
}
