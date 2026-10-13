#include <NavalCommand/Classification/Api/Alignment.h>
#include <NavalCommand/Classification/Api/AssumedAlignment.h>
#include <gtest/gtest.h>

namespace Classification = NavalCommand::Classification::Api;

TEST(AlignmentTest, IncludesDistinctActualAndAssumedAffiliations)
{
	EXPECT_NE(Classification::Alignment::Friendly, Classification::Alignment::Hostile);
	EXPECT_NE(Classification::AssumedAlignment::Friendly, Classification::AssumedAlignment::Hostile);
}
