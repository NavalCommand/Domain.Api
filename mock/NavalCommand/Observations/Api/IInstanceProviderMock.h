#pragma once

#include <NavalCommand/Observations/Api/IInstanceProvider.h>
#include <gmock/gmock.h>

namespace NavalCommand::Observations::Api
{
	class IInstanceProviderMock : public IInstanceProvider
	{
	public:
		MOCK_METHOD((Error::Api::Result<std::vector<Id>>),
			GetObservationIds, (), (const, override));
		MOCK_METHOD((Error::Api::Result<Instance>),
			GetObservationInstance, (const Id& id), (const, override));
	};
}
