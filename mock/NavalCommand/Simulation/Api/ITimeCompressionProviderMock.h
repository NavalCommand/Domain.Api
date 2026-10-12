#pragma once

#include <NavalCommand/Simulation/Api/ITimeCompressionProvider.h>
#include <gmock/gmock.h>

namespace NavalCommand::Simulation::Api
{
	class ITimeCompressionProviderMock : public ITimeCompressionProvider
	{
	public:
		MOCK_METHOD((NavalCommand::Error::Api::Result<TimeCompressionFactor>),
			GetTimeCompression, (), (override));
	};
}
