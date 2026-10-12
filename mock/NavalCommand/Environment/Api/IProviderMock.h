#pragma once

#include <NavalCommand/Environment/Api/ITerrainInfoProvider.h>
#include <gmock/gmock.h>

namespace NavalCommand::Environment::Api
{
	class IProviderMock : public IProvider
	{
	public:
		MOCK_METHOD((NavalCommand::Error::Api::DomainResult<TerrainType, Error>),
			GetTerrainType, (const Physics::Api::Degrees& Latitude, const Physics::Api::Degrees& Longitude),
			(const, override));
		MOCK_METHOD((NavalCommand::Error::Api::DomainResult<Physics::Api::Meters, Error>),
			GetThermalLayerDepth, (const Physics::Api::Degrees& Latitude, const Physics::Api::Degrees& Longitude),
			(const, override));
	};
}
