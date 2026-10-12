#include <NavalCommand/Uncertainty/Api/Resolution.h>
#include <gtest/gtest.h>
#include <cstdint>
#include <string>
#include <variant>

TEST(ResolutionTest, RepresentsUnknownAndEachDeclaredSpecificityLevel)
{
	using TypeResolution = NavalCommand::Uncertainty::Api::Resolution<std::uint32_t, std::string>;
	static_assert(std::variant_size_v<TypeResolution::Variant> == 3);

	const auto unknown = TypeResolution::Unknown();
	const auto number = TypeResolution::Known<std::uint32_t>(42);
	const auto label = TypeResolution::Known<std::string>("tracked");

	EXPECT_TRUE(unknown.IsUnknown());
	EXPECT_FALSE(unknown.IsKnown());
	ASSERT_TRUE(number.IsKnown());
	ASSERT_NE(number.GetIf<std::uint32_t>(), nullptr);
	EXPECT_EQ(*number.GetIf<std::uint32_t>(), 42);
	ASSERT_NE(label.GetIf<std::string>(), nullptr);
	EXPECT_EQ(*label.GetIf<std::string>(), "tracked");
}
