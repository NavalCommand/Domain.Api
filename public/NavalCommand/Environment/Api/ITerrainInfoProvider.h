#pragma once

#include <expected>
#include <NavalCommand/Environment/Api/Error.h>
#include <NavalCommand/Environment/Api/TerrainType.h>
#include <NavalCommand/Error/Api/Result.h>
#include <NavalCommand/Physics/Api/Position.h>

namespace NavalCommand::Environment::Api
{
	class IProvider
	{
	public:
		virtual ~IProvider() = default;

		virtual NavalCommand::Error::Api::DomainResult<TerrainType, Error> GetTerrainType(const Physics::Api::Degrees& Latitude, const Physics::Api::Degrees& Longitude) const = 0;
		virtual NavalCommand::Error::Api::DomainResult<Physics::Api::Meters, Error> GetThermalLayerDepth(const Physics::Api::Degrees& Latitude, const Physics::Api::Degrees& Longitude) const = 0;
	};

}
