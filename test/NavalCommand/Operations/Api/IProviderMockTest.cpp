#include <NavalCommand/Operations/Api/IProviderMock.h>
#include <gmock/gmock.h>
#include <type_traits>

namespace Operations = NavalCommand::Operations::Api;
namespace ErrorApi = NavalCommand::Error::Api;

static_assert(std::is_base_of_v<Operations::IProvider, Operations::IProviderMock>);
static_assert(!std::is_abstract_v<Operations::IProviderMock>);
static_assert(std::is_default_constructible_v<Operations::IProviderMock>);

TEST(OperationsIProviderMockTest, ExpectsUnitStateResultForTrueUnitIdentity)
{
	Operations::IProviderMock mock;
	EXPECT_CALL(mock, GetUnitOperations(testing::_))
		.WillOnce(testing::Return(ErrorApi::Result<Operations::UnitState>{Operations::UnitState{}}));

	EXPECT_TRUE(mock.GetUnitOperations(NavalCommand::Units::Api::Id{"unit-1"}));
}
