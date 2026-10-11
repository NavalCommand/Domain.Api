#pragma once
#include <NavalCommand/World/Api/Knowledge.h>
#include <NavalCommand/World/Api/PositionObservation.h>

namespace NavalCommand::World::Api
{
	// TODO Shouldn't it also encode direction?
	struct KinematicsState
	{
		Knowledge<PositionObservation> Position;
		Knowledge<double> SpeedMetersPerSecond; // TODO use strongly typed units (Like 'struct MetersPerSecond') instead of double. Units require a separate namespace in Domain.Api.
	};
}
