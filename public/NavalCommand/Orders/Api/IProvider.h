#pragma once

#include <expected>
#include <vector>
#include <NavalCommand/Orders/Api/Error.h>
#include <NavalCommand/Orders/Api/Failure.h>
#include <NavalCommand/Orders/Api/ExecutionRequest.h>
#include <NavalCommand/Orders/Api/ExecutionState.h>
#include <NavalCommand/Orders/Api/Id.h>


namespace NavalCommand::Orders::Api
{
	class IProvider
	{
	public:
		virtual ~IProvider() = default;

		virtual std::expected<std::optional<Failure>, Error> CanIssueOrder(const ExecutionRequest& request) const = 0;
		virtual std::expected<Id, Error> IssueOrder(const ExecutionRequest& request) = 0;
		virtual std::expected<ExecutionState, Error> GetOrderState(const Id& id);
	};

}
