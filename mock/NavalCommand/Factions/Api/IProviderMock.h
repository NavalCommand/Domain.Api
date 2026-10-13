#pragma once

#include <NavalCommand/Factions/Api/IProvider.h>
#include <gmock/gmock.h>

namespace NavalCommand::Factions::Api
{
	class IProviderMock : public IProvider
	{
	public:
		MOCK_METHOD((NavalCommand::Error::Api::Result<std::vector<Id>>),
			GetFactionIds, (), (override));
		MOCK_METHOD((NavalCommand::Error::Api::DomainResult<Classification::Api::Alignment, Error>),
			GetFactionAlignment, (const Id& faction1, const Id& faction2), (override));
	};
}
