#include <NavalCommand/Orders/Api/IProviderMock.h>
#include <gmock/gmock.h>
#include <type_traits>

namespace ErrorApi = NavalCommand::Error::Api;
namespace Orders = NavalCommand::Orders::Api;

static_assert(std::is_base_of_v<Orders::IProvider, Orders::IProviderMock>);
static_assert(!std::is_abstract_v<Orders::IProviderMock>);
static_assert(std::is_default_constructible_v<Orders::IProviderMock>);
static_assert(std::is_same_v<decltype(std::declval<const Orders::IProviderMock&>().CanIssueOrder(
	std::declval<const Orders::ExecutionRequest&>())), ErrorApi::Result<std::optional<Orders::Error>>>);
static_assert(std::is_same_v<decltype(std::declval<Orders::IProviderMock&>().IssueOrder(
	std::declval<const Orders::ExecutionRequest&>())), ErrorApi::DomainResult<Orders::Id, Orders::Error>>);

TEST(OrdersIProviderMockTest, PreservesGenericAndDomainFailureTypes)
{
	Orders::IProviderMock mock;
	EXPECT_CALL(mock, CanIssueOrder(testing::_))
		.WillOnce(testing::Return(ErrorApi::Result<std::optional<Orders::Error>>{
			std::unexpected{ErrorApi::Error{ErrorApi::ErrorCondition::NotReady}}}));
	using DomainFailure = ErrorApi::CombinedError<Orders::Error>;
	EXPECT_CALL(mock, IssueOrder(testing::_))
		.WillOnce(testing::Return(ErrorApi::DomainResult<Orders::Id, Orders::Error>{
			std::unexpected{DomainFailure{std::in_place_type<Orders::Error>, Orders::Error::Unsupported}}}));
	EXPECT_CALL(mock, GetOrderState(testing::_))
		.WillOnce(testing::Return(ErrorApi::Result<Orders::ExecutionState>{Orders::ExecutionState{}}));

	Orders::ExecutionRequest request;
	const auto canIssue = mock.CanIssueOrder(request);
	ASSERT_FALSE(canIssue);
	EXPECT_EQ(canIssue.error().Condition, ErrorApi::ErrorCondition::NotReady);
	const auto issue = mock.IssueOrder(request);
	ASSERT_FALSE(issue);
	EXPECT_TRUE(std::holds_alternative<Orders::Error>(issue.error()));
	EXPECT_TRUE(mock.GetOrderState(Orders::Id{"order-1"}));
}
