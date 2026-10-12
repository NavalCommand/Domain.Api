#include <NavalCommand/Units/Api/ITypeProviderMock.h>
#include <gmock/gmock.h>
#include <type_traits>

namespace ErrorApi = NavalCommand::Error::Api;
namespace Units = NavalCommand::Units::Api;

static_assert(std::is_base_of_v<Units::ITypeProvider, Units::ITypeProviderMock>);
static_assert(!std::is_abstract_v<Units::ITypeProviderMock>);
static_assert(std::is_default_constructible_v<Units::ITypeProviderMock>);

TEST(UnitsITypeProviderMockTest, ExpectsTypeQueriesWithDeclaredResults)
{
	Units::ITypeProviderMock mock;
	EXPECT_CALL(mock, GetUnitTypeIds())
		.WillOnce(testing::Return(ErrorApi::Result<std::vector<Units::TypeId>>{
			std::vector<Units::TypeId>{{"carrier"}}}));
	EXPECT_CALL(mock, GetUnitType(testing::_))
		.WillOnce(testing::Return(ErrorApi::Result<Units::Type>{Units::Type{}}));

	EXPECT_EQ(mock.GetUnitTypeIds()->front().Value, "carrier");
	EXPECT_TRUE(mock.GetUnitType(Units::TypeId{"carrier"}));
}
