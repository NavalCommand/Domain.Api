#pragma once
#include <NavalCommand/Physics/Api/MetersPerSecond.h>
#include <NavalCommand/Physics/Api/Position.h>
#include <NavalCommand/Physics/Api/Radians.h>
#include <optional>

namespace NavalCommand::Units::Api
{
	struct KinematicsState
	{
		std::optional<Physics::Api::Position> Position;
		std::optional<Physics::Api::MetersPerSecond> Speed;
		// Clockwise from geodetic north. Heading is body orientation; course is ground movement direction.
		std::optional<Physics::Api::Radians> Heading;
		std::optional<Physics::Api::Radians> CourseOverGround;
	};
}
