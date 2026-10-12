#include <NavalCommand/Observations/Api/IInstanceProviderMock.h>
#include <gmock/gmock.h>
#include <type_traits>

namespace Observations = NavalCommand::Observations::Api;
namespace ErrorApi = NavalCommand::Error::Api;

static_assert(std::is_base_of_v<Observations::IInstanceProvider, Observations::IInstanceProviderMock>);
static_assert(!std::is_abstract_v<Observations::IInstanceProviderMock>);
static_assert(std::is_default_constructible_v<Observations::IInstanceProviderMock>);

TEST(ObservationsIInstanceProviderMockTest, ExpectsConstQueries)
{
	Observations::IInstanceProviderMock mock;
	EXPECT_CALL(mock, GetObservationIds())
		.WillOnce(testing::Return(ErrorApi::Result<std::vector<Observations::Id>>{
			std::vector<Observations::Id>{{"contact-1"}}}));
	EXPECT_CALL(mock, GetObservationInstance(testing::_))
		.WillOnce(testing::Return(ErrorApi::Result<Observations::Instance>{Observations::Instance{}}));

	EXPECT_EQ(mock.GetObservationIds()->front().Value, "contact-1");
	EXPECT_TRUE(mock.GetObservationInstance(Observations::Id{"contact-1"}));
}
