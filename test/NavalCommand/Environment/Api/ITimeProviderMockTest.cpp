#include <NavalCommand/Environment/Api/ITimeProviderMock.h>
#include <gmock/gmock.h>
#include <type_traits>

namespace Environment = NavalCommand::Environment::Api;
namespace ErrorApi = NavalCommand::Error::Api;
namespace Physics = NavalCommand::Physics::Api;

static_assert(std::is_base_of_v<Environment::ITimeProvider, Environment::ITimeProviderMock>);
static_assert(!std::is_abstract_v<Environment::ITimeProviderMock>);
static_assert(std::is_default_constructible_v<Environment::ITimeProviderMock>);

TEST(EnvironmentITimeProviderMockTest, ExpectsCurrentTimeResult)
{
	Environment::ITimeProviderMock mock;
	EXPECT_CALL(mock, GetCurrentTime())
		.WillOnce(testing::Return(ErrorApi::Result<Physics::Seconds>{Physics::Seconds{42.0}}));

	const auto result = mock.GetCurrentTime();
	ASSERT_TRUE(result);
	EXPECT_DOUBLE_EQ(result->Value, 42.0);
}
