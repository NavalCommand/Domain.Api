#pragma once

#include <NavalCommand/Orders/Api/ExecutionRequest.h>
#include <NavalCommand/Orders/Api/Status.h>
#include <NavalCommand/Orders/Api/Failure.h>
#include <NavalCommand/Orders/Api/Id.h>

namespace NavalCommand::Orders::Api
{
	struct ExecutionState
	{
		Id OrderId;
		ExecutionRequest Request;
		std::variant<Status, Failure> OrderStatus;
	};
}
