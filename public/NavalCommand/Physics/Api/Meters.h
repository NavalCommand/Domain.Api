#pragma once

namespace NavalCommand::Physics::Api
{
	struct Meters
	{
		double Value{};
		bool operator==(const Meters&) const = default;
	};
}
