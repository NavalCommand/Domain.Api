#pragma once

namespace NavalCommand::Catalog::Api
{
	struct PlatformDescription
	{
		// Aircraft categories remain aircraft; projectiles and unsupported categories need no platform value.
		enum class Kind
		{
			FixedWingAircraft,
			RotaryWingAircraft,
			SurfaceVessel,
			Submarine,
			LandPlatform
		};

		Kind Category;
	};
}
