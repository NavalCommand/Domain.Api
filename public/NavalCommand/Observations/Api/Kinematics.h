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
		// Reported track heading, clockwise from geodetic north. Unlike Units::Api::Kinematics::Heading,
		// this need not establish physical body orientation: a source may report movement-derived direction.
		// Known means the reported value is available, not that target orientation was independently verified.
		Uncertainty::Api::Exact<Physics::Api::Radians> Heading;
		// Reported ground movement direction. Heading and course may share a source; do not treat them
		// as independent measurements or infer body orientation from their agreement.
		Uncertainty::Api::Exact<Physics::Api::Radians> CourseOverGround;
	};
}
