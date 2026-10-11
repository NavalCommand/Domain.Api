#pragma once

namespace NavalCommand::Physics::Api
{
	struct Radians
	{
		double Value{};
		bool operator==(const Radians&) const = default;
	};
}
