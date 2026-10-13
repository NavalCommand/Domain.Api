#include <NavalCommand/Classification/Api/Category.h>
#include <NavalCommand/Classification/Api/Dimension.h>
#include <NavalCommand/Classification/Api/SubCategory.h>
#include <NavalCommand/Equipment/Api/LoadoutId.h>
#include <NavalCommand/Equipment/Api/TypeId.h>
#include <NavalCommand/Factions/Api/Id.h>
#include <NavalCommand/Observations/Api/Instance.h>
#include <NavalCommand/Physics/Api/Position.h>
#include <NavalCommand/Units/Api/Id.h>
#include <NavalCommand/Units/Api/TypeId.h>
#include <gtest/gtest.h>
#include <optional>
#include <type_traits>
#include <variant>

namespace Classification = NavalCommand::Classification::Api;
namespace Equipment = NavalCommand::Equipment::Api;
namespace Factions = NavalCommand::Factions::Api;
namespace Observations = NavalCommand::Observations::Api;
namespace Physics = NavalCommand::Physics::Api;
namespace Uncertainty = NavalCommand::Uncertainty::Api;
namespace Units = NavalCommand::Units::Api;

using ObservedType = Uncertainty::Resolution<
	Units::TypeId,
	Classification::SubCategory,
	Classification::Category,
	Classification::Dimension>;

static_assert(std::is_same_v<decltype(Observations::Instance::Identity), Observations::Id>);
static_assert(std::is_same_v<decltype(Observations::Instance::Type), ObservedType>);
static_assert(std::is_same_v<decltype(Observations::Instance::CurrentLoadout),
	Uncertainty::Exact<std::optional<Equipment::LoadoutId>>>);
static_assert(std::variant_size_v<ObservedType::Variant> == 5);

TEST(ObservationInstanceTest, RetainsUncertaintyAndSourceAttribution)
{
	Observations::Instance contact;
	contact.Identity = {"blue-contact-9"};
	contact.ObservationName = "track 9";
	contact.ObserverFaction = Factions::Id{"blue"};
	contact.ObservedFaction = Uncertainty::Exact<Factions::Id>::Unknown();
	contact.Type = ObservedType::Known<Units::TypeId>({"possible-aircraft"});
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

TEST(ObservationInstanceTest, SupportsEveryIdentificationResolution)
{
	ObservedType type;
	EXPECT_TRUE(type.IsUnknown());

	type = ObservedType::Known<Classification::Dimension>(Classification::Dimension::Air);
	EXPECT_EQ(*type.GetIf<Classification::Dimension>(), Classification::Dimension::Air);

	type = ObservedType::Known<Classification::Category>(Classification::Category::Aircraft);
	EXPECT_EQ(*type.GetIf<Classification::Category>(), Classification::Category::Aircraft);
	EXPECT_EQ(type.GetIf<Classification::Dimension>(), nullptr);

	type = ObservedType::Known<Classification::SubCategory>(Classification::SubCategory::FixedWingAircraft);
	EXPECT_EQ(*type.GetIf<Classification::SubCategory>(), Classification::SubCategory::FixedWingAircraft);

	type = ObservedType::Known<Units::TypeId>({"f14a"});
	ASSERT_NE(type.GetIf<Units::TypeId>(), nullptr);
	EXPECT_EQ(type.GetIf<Units::TypeId>()->Value, "f14a");
}

TEST(ObservationInstanceTest, DistinguishesUnknownAbsentAndSelectedLoadouts)
{
	Observations::Instance contact;
	EXPECT_FALSE(contact.CurrentLoadout.IsKnown());

	using ObservedLoadout = Uncertainty::Exact<std::optional<Equipment::LoadoutId>>;
	contact.CurrentLoadout = ObservedLoadout::Known(std::nullopt);
	ASSERT_TRUE(contact.CurrentLoadout.IsKnown());
	EXPECT_FALSE(contact.CurrentLoadout.Value().has_value());

	contact.CurrentLoadout = ObservedLoadout::Known(
		std::optional<Equipment::LoadoutId>{Equipment::LoadoutId{"anti-submarine"}});
	ASSERT_TRUE(contact.CurrentLoadout.IsKnown());
	ASSERT_TRUE(contact.CurrentLoadout.Value().has_value());
	EXPECT_EQ(contact.CurrentLoadout.Value()->Value, "anti-submarine");

	contact.CurrentLoadout = ObservedLoadout::Unknown();
	EXPECT_FALSE(contact.CurrentLoadout.IsKnown());
}
