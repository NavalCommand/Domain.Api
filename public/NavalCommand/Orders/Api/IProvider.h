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

		virtual std::optional<Failure> CanIssueOrder(const ExecutionRequest& request) const = 0;
		virtual Id IssueOrder(const ExecutionRequest& request) = 0;
		virtual std::expected<ExecutionState, Error> GetOrderState(const Id& id);
	};

}
