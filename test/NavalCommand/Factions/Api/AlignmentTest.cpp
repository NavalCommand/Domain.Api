#include <NavalCommand/Factions/Api/Alignment.h>
#include <gtest/gtest.h>

TEST(AlignmentTest, IncludesFriendly)
{
	EXPECT_NE(NavalCommand::Factions::Api::Alignment::Friendly,
		NavalCommand::Factions::Api::Alignment::Hostile);
}
