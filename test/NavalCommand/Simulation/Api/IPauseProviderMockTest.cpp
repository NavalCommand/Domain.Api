#include <NavalCommand/Simulation/Api/IPauseProviderMock.h>
#include <gmock/gmock.h>
#include <type_traits>

namespace ErrorApi = NavalCommand::Error::Api;
namespace Simulation = NavalCommand::Simulation::Api;

static_assert(std::is_base_of_v<Simulation::IPauseProvider, Simulation::IPauseProviderMock>);
static_assert(!std::is_abstract_v<Simulation::IPauseProviderMock>);
static_assert(std::is_default_constructible_v<Simulation::IPauseProviderMock>);

TEST(IPauseProviderMockTest, ExpectsPausedStateResult)
{
	Simulation::IPauseProviderMock mock;
	EXPECT_CALL(mock, IsPaused()).WillOnce(testing::Return(ErrorApi::Result<bool>{true}));
	EXPECT_TRUE(*mock.IsPaused());
}
