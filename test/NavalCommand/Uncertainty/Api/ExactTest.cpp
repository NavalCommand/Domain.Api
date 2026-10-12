#include <NavalCommand/Uncertainty/Api/Exact.h>
#include <gtest/gtest.h>
#include <cstdint>

TEST(ExactTest, DistinguishesKnownValuesFromUnknown)
{
	const auto unknown = NavalCommand::Uncertainty::Api::Exact<std::uint32_t>::Unknown();
	const auto knownZero = NavalCommand::Uncertainty::Api::Exact<std::uint32_t>::Known(0);
	const auto knownFalse = NavalCommand::Uncertainty::Api::Exact<bool>::Known(false);

	EXPECT_FALSE(unknown.HasValue());
	EXPECT_FALSE(unknown.IsKnown());
	EXPECT_TRUE(knownZero.IsKnown());
	EXPECT_EQ(knownZero.Value(), 0);
	EXPECT_TRUE(knownFalse.HasValue());
	EXPECT_FALSE(knownFalse.Value());
}
