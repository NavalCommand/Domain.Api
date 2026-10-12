#include <NavalCommand/Orders/Api/ExecutionState.h>
#include <gtest/gtest.h>
#include <variant>

TEST(ExecutionStateTest, StoresTheRequestAndPendingStatus)
{
	NavalCommand::Orders::Api::ExecutionState state;
	state.OrderId = {"order-7"};
	state.Request.Executor = {"unit-1"};
	state.OrderStatus = NavalCommand::Orders::Api::Status::Pending;

	EXPECT_EQ(state.OrderId.Value, "order-7");
	ASSERT_TRUE(std::holds_alternative<NavalCommand::Orders::Api::Status>(state.OrderStatus));
	EXPECT_EQ(std::get<NavalCommand::Orders::Api::Status>(state.OrderStatus),
		NavalCommand::Orders::Api::Status::Pending);
}
