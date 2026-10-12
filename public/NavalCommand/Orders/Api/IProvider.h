#pragma once

#include <expected>
#include <vector>
#include <NavalCommand/Error/Api/Result.h>
#include <NavalCommand/Orders/Api/Error.h>
#include <NavalCommand/Orders/Api/Error.h>
#include <NavalCommand/Orders/Api/ExecutionRequest.h>
#include <NavalCommand/Orders/Api/ExecutionState.h>
#include <NavalCommand/Orders/Api/Id.h>


namespace NavalCommand::Orders::Api
{
	class IProvider
	{
	public:
		virtual ~IProvider() = default;

		virtual NavalCommand::Error::Api::Result<std::optional<Error>> CanIssueOrder(const ExecutionRequest& request) const = 0;
		virtual NavalCommand::Error::Api::DomainResult<Id, Error> IssueOrder(const ExecutionRequest& request) = 0;
		virtual NavalCommand::Error::Api::Result<ExecutionState> GetOrderState(const Id& id);
	};

}
