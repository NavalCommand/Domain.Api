#include <NavalCommand/Simulation/Api/ITimeCompressionControllerMock.h>
#include <gmock/gmock.h>
#include <type_traits>

namespace ErrorApi = NavalCommand::Error::Api;
namespace Simulation = NavalCommand::Simulation::Api;

static_assert(std::is_base_of_v<Simulation::ITimeCompressionController,
	Simulation::ITimeCompressionControllerMock>);
static_assert(!std::is_abstract_v<Simulation::ITimeCompressionControllerMock>);
static_assert(std::is_default_constructible_v<Simulation::ITimeCompressionControllerMock>);

TEST(ITimeCompressionControllerMockTest, ExpectsDomainResultForSettingTheFactor)
{
	Simulation::ITimeCompressionControllerMock mock;
	EXPECT_CALL(mock, SetTimeCompression(Simulation::TimeCompressionFactor{2.0}))
		.WillOnce(testing::Return(ErrorApi::DomainResult<void, Simulation::Error>{}));
	EXPECT_TRUE(mock.SetTimeCompression(Simulation::TimeCompressionFactor{2.0}));
}
