#pragma once
#include <NavalCommand/World/Api/Knowledge.h>
#include <NavalCommand/World/Api/PositionObservation.h>

namespace NavalCommand::World::Api
{
	struct KinematicsState
	{
		Knowledge<PositionObservation> Position;
		Knowledge<double> SpeedMetersPerSecond;
	};
}
