#pragma once
#include <optional>

namespace NavalCommand::Catalog::Api
{
	struct PlatformDescription
	{
		enum class Kind
		{
			Aircraft,
			SurfaceVessel,
			Submarine,
			LandPlatform
		};

		enum class AircraftKind
		{
			FixedWing,
			RotaryWing
		};

		Kind Category{};
		// Present only for Aircraft. A helicopter is aircraft with RotaryWing classification.
		std::optional<AircraftKind> Aircraft;
	};
}
