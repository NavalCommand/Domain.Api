#pragma once
#include <NavalCommand/Orders/Api/RouteMode.h>

namespace NavalCommand::Orders::Api
{
	struct RouteCommand
	{
		double latitudeDeg{};
		double longitudeDeg{};
		RouteMode routeMode{};
	};
}
