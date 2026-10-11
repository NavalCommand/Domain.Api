#pragma once

namespace NavalCommand::Orders::Api
{
	// Only implemented high-level orders. Dispatch revalidates authority and current native safety.
	enum class OrderKind
	{
		ReplaceRoute,
		AppendRoute,
		IdleWaypoint,
		LaunchAircraft
	};
}
