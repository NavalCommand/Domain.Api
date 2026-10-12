#pragma once

#include <NavalCommand/Environment/Api/ITimeProvider.h>
#include <gmock/gmock.h>

namespace NavalCommand::Environment::Api
{
	class ITimeProviderMock : public ITimeProvider
	{
	public:
		MOCK_METHOD((NavalCommand::Error::Api::Result<Physics::Api::Seconds>),
			GetCurrentTime, (), (override));
	};
}
