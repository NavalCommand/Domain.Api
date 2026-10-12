#pragma once

#include <NavalCommand/Simulation/Api/IPauseController.h>
#include <gmock/gmock.h>

namespace NavalCommand::Simulation::Api
{
	class IPauseControllerMock : public IPauseController
	{
	public:
		MOCK_METHOD((NavalCommand::Error::Api::Result<bool>),
			CanRequestPause, (), (const, override));
		MOCK_METHOD((NavalCommand::Error::Api::Result<bool>),
			CanRequestUnpause, (), (const, override));
		MOCK_METHOD((NavalCommand::Error::Api::DomainResult<void, Error>),
			RequestPause, (bool paused), (override));
	};
}
