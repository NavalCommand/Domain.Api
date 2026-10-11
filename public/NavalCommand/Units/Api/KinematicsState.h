#pragma once
#include <NavalCommand/Physics/Api/MetersPerSecond.h>
#include <NavalCommand/Physics/Api/Radians.h>
#include <NavalCommand/Uncertainty/Api/Knowledge.h>
#include <NavalCommand/Units/Api/PositionObservation.h>

namespace NavalCommand::Units::Api
{
	struct KinematicsState
	{
		Uncertainty::Api::Knowledge<PositionObservation> Position;
		Uncertainty::Api::Knowledge<Physics::Api::MetersPerSecond> Speed;
		// Clockwise from geodetic north. Heading is body orientation, not ground-track direction.
		Uncertainty::Api::Knowledge<Physics::Api::Radians> Heading;
		Uncertainty::Api::Knowledge<Physics::Api::Radians> CourseOverGround;
	};
}
