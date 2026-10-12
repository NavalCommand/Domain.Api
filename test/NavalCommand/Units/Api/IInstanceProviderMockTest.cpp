#include <NavalCommand/Units/Api/IInstanceProviderMock.h>
#include <gmock/gmock.h>
#include <type_traits>

namespace ErrorApi = NavalCommand::Error::Api;
namespace Units = NavalCommand::Units::Api;

static_assert(std::is_base_of_v<Units::IInstanceProvider, Units::IInstanceProviderMock>);
static_assert(!std::is_abstract_v<Units::IInstanceProviderMock>);
static_assert(std::is_default_constructible_v<Units::IInstanceProviderMock>);

TEST(UnitsIInstanceProviderMockTest, ExpectsBothConstInstanceQueries)
{
	Units::IInstanceProviderMock mock;
	EXPECT_CALL(mock, GetUnitInstanceIds())
		.WillOnce(testing::Return(ErrorApi::Result<std::vector<Units::Id>>{
			std::vector<Units::Id>{{"unit-1"}}}));
	EXPECT_CALL(mock, GetUnitInstance(testing::_))
		.WillOnce(testing::Return(ErrorApi::Result<Units::Instance>{Units::Instance{}}));

	EXPECT_EQ(mock.GetUnitInstanceIds()->front().Value, "unit-1");
	EXPECT_TRUE(mock.GetUnitInstance(Units::Id{"unit-1"}));
}
