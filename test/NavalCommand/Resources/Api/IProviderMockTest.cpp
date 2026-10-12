#include <NavalCommand/Resources/Api/IProviderMock.h>
#include <gmock/gmock.h>
#include <type_traits>

namespace ErrorApi = NavalCommand::Error::Api;
namespace Resources = NavalCommand::Resources::Api;

static_assert(std::is_base_of_v<Resources::IProvider, Resources::IProviderMock>);
static_assert(!std::is_abstract_v<Resources::IProviderMock>);
static_assert(std::is_default_constructible_v<Resources::IProviderMock>);

TEST(ResourcesIProviderMockTest, ExpectsConstIdentifierAndDefinitionQueries)
{
	Resources::IProviderMock mock;
	EXPECT_CALL(mock, GetResourceIds())
		.WillOnce(testing::Return(ErrorApi::Result<std::vector<Resources::Id>>{
			std::vector<Resources::Id>{{"fuel"}}}));
	EXPECT_CALL(mock, GetResourceDefinition(testing::_))
		.WillOnce(testing::Return(ErrorApi::Result<std::vector<Resources::Definition>>{
			std::vector<Resources::Definition>{Resources::Definition{}}}));

	EXPECT_EQ(mock.GetResourceIds()->front().Value, "fuel");
	EXPECT_EQ(mock.GetResourceDefinition(Resources::Id{"fuel"})->size(), 1);
}
