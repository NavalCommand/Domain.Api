#include <NavalCommand/Observations/Api/Instance.h>
#include <NavalCommand/Equipment/Api/TypeId.h>
#include <NavalCommand/Factions/Api/Id.h>
#include <NavalCommand/Physics/Api/Position.h>
#include <NavalCommand/Units/Api/Classification.h>
#include <NavalCommand/Units/Api/Id.h>
#include <NavalCommand/Units/Api/TypeId.h>
#include <gtest/gtest.h>
#include <type_traits>
#include <variant>

namespace Equipment = NavalCommand::Equipment::Api;
namespace Factions = NavalCommand::Factions::Api;
namespace Observations = NavalCommand::Observations::Api;
namespace Physics = NavalCommand::Physics::Api;
namespace Uncertainty = NavalCommand::Uncertainty::Api;
namespace Units = NavalCommand::Units::Api;

static_assert(std::is_same_v<decltype(Observations::Instance::Identity), Observations::Id>);
static_assert(std::is_same_v<decltype(Observations::Instance::Type),
	Uncertainty::Resolution<Units::TypeId, Units::Classification>>);

TEST(ObservationInstanceTest, RetainsUncertaintyAndSourceAttribution)
{
	Observations::Instance contact;
	contact.Identity = {"blue-contact-9"};
	contact.ObservationName = "track 9";
	contact.ObserverFaction = Factions::Id{"blue"};
	contact.ObservedFaction = Uncertainty::Exact<Factions::Id>::Unknown();
	contact.Type = Uncertainty::Resolution<Units::TypeId, Units::Classification>::
		Known<Units::TypeId>({"possible-aircraft"});
	contact.Kinematics.Position = Physics::Position{{61.9}, {-10.3}, {0}};
	contact.Aircraft.emplace();
	contact.Aircraft->Airborne = Uncertainty::Exact<bool>::Known(false);
	contact.Contributors.push_back({Units::Id{"observer-unit"}, {Equipment::TypeId{"search-radar"}}});

	const auto* resolvedType = contact.Type.GetIf<Units::TypeId>();
	ASSERT_NE(resolvedType, nullptr);
	EXPECT_EQ(resolvedType->Value, "possible-aircraft");
	EXPECT_FALSE(contact.ObservedFaction.IsKnown());
	ASSERT_TRUE(contact.Aircraft.has_value());
	EXPECT_TRUE(contact.Aircraft->Airborne.IsKnown());
	EXPECT_FALSE(contact.Aircraft->Airborne.Value());
	EXPECT_DOUBLE_EQ(std::get<Physics::Position>(contact.Kinematics.Position).Latitude.Value, 61.9);
	ASSERT_EQ(contact.Contributors.size(), 1);
}
