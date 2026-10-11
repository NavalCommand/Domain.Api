#pragma once
#include <optional>

namespace NavalCommand::World::Api
{
	// TODO Physical Traits of what?
	struct PhysicalTraits
	{
		struct Arc
		{
			double StartRadians;
			double EndRadians;
		};

		std::optional<Arc> HorizontalArc;
		std::optional<double> OrientationRadians;
	};
}
