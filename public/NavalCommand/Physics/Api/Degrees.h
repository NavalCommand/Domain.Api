#pragma once

namespace NavalCommand::Physics::Api
{
	struct Degrees
	{
		double Value{};
		bool operator==(const Degrees&) const = default;
	};
}
