#pragma once

#include <expected>
#include <vector>
#include <NavalCommand/Environment/Api/Error.h>
#include <NavalCommand/Environment/Api/TerrainType.h>
#include <NavalCommand/Physics/Api/Position.h>

namespace NavalCommand::Environment::Api
{
	class IProvider
	{
	public:
		virtual ~IProvider() = default;

		virtual std::expected<TerrainType, Error> GetTerrainType(const Physics::Api::Degrees& Latitude, const Physics::Api::Degrees& Longitude) const = 0;
		virtual std::expected<Physics::Api::Meters, Error> GetThermalLayerDepth(const Physics::Api::Degrees& Latitude, const Physics::Api::Degrees& Longitude) const = 0;
	};

}
