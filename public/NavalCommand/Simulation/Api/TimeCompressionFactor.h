#pragma once

namespace NavalCommand::Simulation::Api
{
	struct TimeCompressionFactor
	{
		double Value;
		bool operator==(const TimeCompressionFactor&) const = default;
	};
}
