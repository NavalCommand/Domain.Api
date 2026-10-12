#include <NavalCommand/Simulation/Api/IPauseControllerMock.h>
#include <gmock/gmock.h>
#include <type_traits>

namespace ErrorApi = NavalCommand::Error::Api;
namespace Simulation = NavalCommand::Simulation::Api;

static_assert(std::is_base_of_v<Simulation::IPauseController, Simulation::IPauseControllerMock>);
static_assert(!std::is_abstract_v<Simulation::IPauseControllerMock>);
static_assert(std::is_default_constructible_v<Simulation::IPauseControllerMock>);

TEST(IPauseControllerMockTest, ExpectsPermissionAndPauseRequests)
{
	Simulation::IPauseControllerMock mock;
	EXPECT_CALL(mock, CanRequestPause()).WillOnce(testing::Return(ErrorApi::Result<bool>{true}));
	EXPECT_CALL(mock, CanRequestUnpause()).WillOnce(testing::Return(ErrorApi::Result<bool>{false}));
	EXPECT_CALL(mock, RequestPause(true))
		.WillOnce(testing::Return(ErrorApi::DomainResult<void, Simulation::Error>{}));

	EXPECT_TRUE(*mock.CanRequestPause());
	EXPECT_FALSE(*mock.CanRequestUnpause());
	EXPECT_TRUE(mock.RequestPause(true));
}
