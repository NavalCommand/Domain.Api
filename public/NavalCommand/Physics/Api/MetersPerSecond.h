#pragma once

namespace NavalCommand::Physics::Api
{
	struct MetersPerSecond
	{
		double Value{};
		bool operator==(const MetersPerSecond&) const = default;
	};
}
