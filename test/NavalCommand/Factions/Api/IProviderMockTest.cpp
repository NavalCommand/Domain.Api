#include <NavalCommand/Classification/Api/Alignment.h>
#include <NavalCommand/Factions/Api/IProviderMock.h>
#include <gmock/gmock.h>
#include <type_traits>

namespace Classification = NavalCommand::Classification::Api;
namespace Factions = NavalCommand::Factions::Api;
namespace ErrorApi = NavalCommand::Error::Api;

static_assert(std::is_base_of_v<Factions::IProvider, Factions::IProviderMock>);
static_assert(!std::is_abstract_v<Factions::IProviderMock>);
static_assert(std::is_default_constructible_v<Factions::IProviderMock>);

TEST(FactionsIProviderMockTest, ExpectsFactionQueries)
{
	Factions::IProviderMock mock;
	EXPECT_CALL(mock, GetFactionIds())
		.WillOnce(testing::Return(ErrorApi::Result<std::vector<Factions::Id>>{
			std::vector<Factions::Id>{{"blue"}}}));
	EXPECT_CALL(mock, GetFactionAlignment(testing::_, testing::_))
		.WillOnce(testing::Return(ErrorApi::DomainResult<Classification::Alignment, Factions::Error>{
			Classification::Alignment::Friendly}));

	EXPECT_EQ(mock.GetFactionIds()->front().Value, "blue");
	EXPECT_EQ(*mock.GetFactionAlignment(Factions::Id{"blue"}, Factions::Id{"blue"}),
		Classification::Alignment::Friendly);
}
