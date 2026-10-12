#include <NavalCommand/Operations/Api/Activity.h>
#include <NavalCommand/Observations/Api/Id.h>
#include <NavalCommand/Physics/Api/Position.h>
#include <NavalCommand/Physics/Api/Radians.h>
#include <NavalCommand/Uncertainty/Api/Exact.h>
#include <gtest/gtest.h>
#include <type_traits>
#include <variant>

namespace Observations = NavalCommand::Observations::Api;
namespace Operations = NavalCommand::Operations::Api;
namespace Physics = NavalCommand::Physics::Api;
namespace Uncertainty = NavalCommand::Uncertainty::Api;

using ExpectedEngagementTarget = std::variant<std::monostate, Observations::Id,
	Physics::Position, Physics::Radians>;
static_assert(std::is_same_v<decltype(Operations::EngagingWith::Target), ExpectedEngagementTarget>);
static_assert(std::is_same_v<decltype(Operations::EvasiveManeuvers::DangerSource),
	Uncertainty::Exact<Observations::Id>>);

TEST(ActivityTest, EngagementTargetUsesObservationIdentity)
{
	Operations::EngagingWith engagement;
	engagement.Target = Observations::Id{"contact-1"};

	ASSERT_TRUE(std::holds_alternative<Observations::Id>(engagement.Target));
	EXPECT_EQ(std::get<Observations::Id>(engagement.Target).Value, "contact-1");
}
