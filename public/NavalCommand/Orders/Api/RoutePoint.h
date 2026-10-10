#pragma once
#include <string>

namespace NavalCommand::Orders::Api
{
	struct RoutePoint
	{
		double latitudeDeg{};
		double longitudeDeg{};
		std::string label;
	};
}
