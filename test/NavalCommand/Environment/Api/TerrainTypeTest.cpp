#include <NavalCommand/Environment/Api/TerrainType.h>
#include <gtest/gtest.h>

TEST(TerrainTypeTest, IncludesWater)
{
	EXPECT_NE(NavalCommand::Environment::Api::TerrainType::Water,
		NavalCommand::Environment::Api::TerrainType::Land);
}
