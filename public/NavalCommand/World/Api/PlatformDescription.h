#pragma once
#include <variant>

namespace NavalCommand::World::Api
{
	struct PlatformDescription
	{
		struct Aircraft
		{
		};

		// TODO Isn't Helicopter an Aircraft?
		struct Helicopter
		{
		};

		struct SurfaceVessel
		{
		};

		struct Submarine
		{
		};

		struct LandPlatform
		{
		};

		std::variant<Aircraft, Helicopter, SurfaceVessel, Submarine, LandPlatform> Description;
	};
}
