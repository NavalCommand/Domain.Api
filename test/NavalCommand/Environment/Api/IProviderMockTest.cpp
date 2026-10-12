#include <NavalCommand/Environment/Api/IProviderMock.h>
#include <gmock/gmock.h>
#include <type_traits>

namespace Environment = NavalCommand::Environment::Api;
namespace ErrorApi = NavalCommand::Error::Api;
namespace Physics = NavalCommand::Physics::Api;

static_assert(std::is_base_of_v<Environment::IProvider, Environment::IProviderMock>);
static_assert(!std::is_abstract_v<Environment::IProviderMock>);
static_assert(std::is_default_constructible_v<Environment::IProviderMock>);

TEST(EnvironmentIProviderMockTest, ExpectsBothDomainResultMethods)
{
	Environment::IProviderMock mock;
	EXPECT_CALL(mock, GetTerrainType(testing::_, testing::_))
		.WillOnce(testing::Return(ErrorApi::DomainResult<Environment::TerrainType, Environment::Error>{
			Environment::TerrainType::Water}));
	EXPECT_CALL(mock, GetThermalLayerDepth(testing::_, testing::_))
		.WillOnce(testing::Return(ErrorApi::DomainResult<Physics::Meters, Environment::Error>{Physics::Meters{80.0}}));

	EXPECT_TRUE(mock.GetTerrainType(Physics::Degrees{61.0}, Physics::Degrees{-10.0}));
	EXPECT_TRUE(mock.GetThermalLayerDepth(Physics::Degrees{61.0}, Physics::Degrees{-10.0}));
}
