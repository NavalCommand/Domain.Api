#pragma once
#include <NavalCommand/Physics/Api/MetersPerSecond.h>
#include <NavalCommand/Physics/Api/Position.h>
#include <NavalCommand/Physics/Api/Radians.h>
#include <NavalCommand/Uncertainty/Api/Knowledge.h>

namespace NavalCommand::Observations::Api
{
	struct ObservedKinematics
	{
		Uncertainty::Api::Knowledge<Physics::Api::Position> Position;
		Uncertainty::Api::Knowledge<Physics::Api::MetersPerSecond> Speed;
		Uncertainty::Api::Knowledge<Physics::Api::Radians> Heading;
		Uncertainty::Api::Knowledge<Physics::Api::Radians> CourseOverGround;
	};
}
