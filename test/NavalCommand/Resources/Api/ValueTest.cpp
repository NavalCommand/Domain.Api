#include <NavalCommand/Resources/Api/Value.h>
#include <gtest/gtest.h>
#include <cstdint>
#include <variant>

static_assert(std::variant_size_v<NavalCommand::Resources::Api::Value> == 2);

TEST(ResourceValueTest, RepresentsDiscreteAndContinuousValues)
{
	NavalCommand::Resources::Api::Value inventory = std::uint64_t{0};
	NavalCommand::Resources::Api::Value fuel = 0.3;
	ASSERT_TRUE(std::holds_alternative<std::uint64_t>(inventory));
	EXPECT_EQ(std::get<std::uint64_t>(inventory), 0);
	ASSERT_TRUE(std::holds_alternative<double>(fuel));
	EXPECT_DOUBLE_EQ(std::get<double>(fuel), 0.3);
}
