#pragma once
#include <NavalCommand/Physics/Api/Meters.h>
#include <NavalCommand/Physics/Api/Radians.h>

namespace NavalCommand::Observations::Api
{
	struct ObservedErrorEllipse
	{
		Physics::Api::Meters MajorAxis;
		Physics::Api::Meters MinorAxis;
		Physics::Api::Radians Orientation;
	};
}
