#pragma once

#include <NavalCommand/Units/Api/IInstanceProvider.h>
#include <gmock/gmock.h>

namespace NavalCommand::Units::Api
{
	class IInstanceProviderMock : public IInstanceProvider
	{
	public:
		MOCK_METHOD((Error::Api::Result<std::vector<Id>>),
			GetUnitInstanceIds, (), (const, override));
		MOCK_METHOD((Error::Api::Result<Instance>),
			GetUnitInstance, (const Id& unitInstanceId), (const, override));
	};
}
