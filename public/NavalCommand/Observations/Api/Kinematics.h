#pragma once
#include <NavalCommand/Observations/Api/Position.h>
#include <NavalCommand/Physics/Api/MetersPerSecond.h>
#include <NavalCommand/Physics/Api/Radians.h>
#include <NavalCommand/Uncertainty/Api/Exact.h>

namespace NavalCommand::Observations::Api
{
	struct Kinematics
	{
		Position Position;
		Uncertainty::Api::Exact<Physics::Api::MetersPerSecond> Speed;
		Uncertainty::Api::Exact<Physics::Api::Radians> Heading;
		Uncertainty::Api::Exact<Physics::Api::Radians> CourseOverGround;
	};
}
