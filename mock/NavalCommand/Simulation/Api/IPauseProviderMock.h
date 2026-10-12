#pragma once

#include <NavalCommand/Simulation/Api/IPauseProvider.h>
#include <gmock/gmock.h>

namespace NavalCommand::Simulation::Api
{
	class IPauseProviderMock : public IPauseProvider
	{
	public:
		MOCK_METHOD((NavalCommand::Error::Api::Result<bool>), IsPaused, (), (const, override));
	};
}
