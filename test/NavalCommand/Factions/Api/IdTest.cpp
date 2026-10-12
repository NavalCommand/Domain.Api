#include <NavalCommand/Factions/Api/Id.h>
#include <gtest/gtest.h>

TEST(FactionIdTest, StoresItsValue)
{
	const NavalCommand::Factions::Api::Id id{"blue"};
	EXPECT_EQ(id.Value, "blue");
}
