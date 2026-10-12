#include <NavalCommand/Simulation/Api/ITimeCompressionProviderMock.h>
#include <gmock/gmock.h>
#include <type_traits>

namespace ErrorApi = NavalCommand::Error::Api;
namespace Simulation = NavalCommand::Simulation::Api;

static_assert(std::is_base_of_v<Simulation::ITimeCompressionProvider,
	Simulation::ITimeCompressionProviderMock>);
static_assert(!std::is_abstract_v<Simulation::ITimeCompressionProviderMock>);
static_assert(std::is_default_constructible_v<Simulation::ITimeCompressionProviderMock>);

TEST(ITimeCompressionProviderMockTest, ExpectsCurrentFactorResult)
{
	Simulation::ITimeCompressionProviderMock mock;
	EXPECT_CALL(mock, GetTimeCompression())
		.WillOnce(testing::Return(ErrorApi::Result<Simulation::TimeCompressionFactor>{
			Simulation::TimeCompressionFactor{4.0}}));
	EXPECT_EQ(*mock.GetTimeCompression(), Simulation::TimeCompressionFactor{4.0});
}
