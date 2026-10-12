#include <NavalCommand/Observations/Api/Id.h>
#include <NavalCommand/Units/Api/Id.h>
#include <gtest/gtest.h>
#include <type_traits>

namespace Observations = NavalCommand::Observations::Api;
namespace Units = NavalCommand::Units::Api;

static_assert(!std::is_same_v<Observations::Id, Units::Id>);

TEST(ObservationIdTest, RepresentsAnObserverSideContact)
{
	const Observations::Id id{"blue-contact-9"};
	EXPECT_EQ(id.Value, "blue-contact-9");
}
