#pragma once

#include <NavalCommand/Resources/Api/IProvider.h>
#include <gmock/gmock.h>

namespace NavalCommand::Resources::Api
{
	class IProviderMock : public IProvider
	{
	public:
		MOCK_METHOD((Error::Api::Result<std::vector<Id>>),
			GetResourceIds, (), (const, override));
		MOCK_METHOD((Error::Api::Result<std::vector<Definition>>),
			GetResourceDefinition, (const Id& id), (const, override));
	};
}
