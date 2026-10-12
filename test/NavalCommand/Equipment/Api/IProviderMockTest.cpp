#include <NavalCommand/Equipment/Api/IProviderMock.h>
#include <gmock/gmock.h>
#include <type_traits>

namespace Equipment = NavalCommand::Equipment::Api;
namespace ErrorApi = NavalCommand::Error::Api;

static_assert(std::is_base_of_v<Equipment::IProvider, Equipment::IProviderMock>);
static_assert(!std::is_abstract_v<Equipment::IProviderMock>);
static_assert(std::is_default_constructible_v<Equipment::IProviderMock>);

TEST(EquipmentIProviderMockTest, ExpectsGenericAndDomainSpecificResults)
{
	Equipment::IProviderMock mock;
	EXPECT_CALL(mock, GetEquipmentType(testing::_))
		.WillOnce(testing::Return(ErrorApi::DomainResult<Equipment::Type, Equipment::Error>{Equipment::Type{}}));
	EXPECT_CALL(mock, GetEquipmentTypes())
		.WillOnce(testing::Return(ErrorApi::Result<std::vector<Equipment::TypeId>>{
			std::vector<Equipment::TypeId>{{"radar"}}}));

	EXPECT_TRUE(mock.GetEquipmentType(Equipment::TypeId{"radar"}));
	const auto types = mock.GetEquipmentTypes();
	ASSERT_TRUE(types);
	ASSERT_EQ(types->size(), 1);
	EXPECT_EQ(types->front().Value, "radar");
}
