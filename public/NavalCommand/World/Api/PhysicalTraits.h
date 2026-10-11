#pragma once
#include <optional>

namespace NavalCommand::World::Api
{
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
