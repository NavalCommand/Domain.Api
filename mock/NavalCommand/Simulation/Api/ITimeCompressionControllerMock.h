#pragma once

#include <NavalCommand/Simulation/Api/ITimeCompressionController.h>
#include <gmock/gmock.h>

namespace NavalCommand::Simulation::Api
{
	class ITimeCompressionControllerMock : public ITimeCompressionController
	{
	public:
		MOCK_METHOD((NavalCommand::Error::Api::DomainResult<void, Error>),
			SetTimeCompression, (TimeCompressionFactor factor), (override));
	};
}
