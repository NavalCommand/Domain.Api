#include <NavalCommand/Environment/Api/IWeatherProviderMock.h>
#include <gtest/gtest.h>
#include <type_traits>

namespace Environment = NavalCommand::Environment::Api;

static_assert(std::is_base_of_v<Environment::IWeatherProvider, Environment::IWeatherProviderMock>);
static_assert(!std::is_abstract_v<Environment::IWeatherProviderMock>);
static_assert(std::is_default_constructible_v<Environment::IWeatherProviderMock>);

TEST(EnvironmentIWeatherProviderMockTest, InstantiatesWithoutInventedOperations)
{
	const Environment::IWeatherProviderMock mock;
	SUCCEED();
}
