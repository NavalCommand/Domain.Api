#include <NavalCommand/Resources/Api/Definition.h>
#include <gtest/gtest.h>

TEST(ResourceDefinitionTest, DeclaresCountedConsumableMissiles)
{
	using Definition = NavalCommand::Resources::Api::Definition;
	Definition missiles;
	missiles.Id = {"missile-rounds"};
	missiles.Representation = Definition::NumericRepresentation::Discrete;
	missiles.Unit = Definition::MeasurementUnit::Count;
	missiles.Accounting = Definition::AccountingSemantics::Consumable;

	EXPECT_EQ(missiles.Id.Value, "missile-rounds");
	EXPECT_EQ(missiles.Representation, Definition::NumericRepresentation::Discrete);
	EXPECT_EQ(missiles.Unit, Definition::MeasurementUnit::Count);
	EXPECT_EQ(missiles.Accounting, Definition::AccountingSemantics::Consumable);
}
