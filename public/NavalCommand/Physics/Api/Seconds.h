#pragma once

namespace NavalCommand::Physics::Api
{
	struct Seconds
	{
		double Value{};
		bool operator==(const Seconds&) const = default;
	};
}
