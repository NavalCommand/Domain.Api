#pragma once

#include <NavalCommand/Orders/Api/IProvider.h>
#include <gmock/gmock.h>

namespace NavalCommand::Orders::Api
{
	class IProviderMock : public IProvider
	{
	public:
		MOCK_METHOD((NavalCommand::Error::Api::Result<std::optional<Error>>),
			CanIssueOrder, (const ExecutionRequest& request), (const, override));
		MOCK_METHOD((NavalCommand::Error::Api::DomainResult<Id, Error>),
			IssueOrder, (const ExecutionRequest& request), (override));
		MOCK_METHOD((NavalCommand::Error::Api::Result<ExecutionState>),
			GetOrderState, (const Id& id), (override));
	};
}
