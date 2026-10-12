#include <NavalCommand/Error/Api/MakeError.h>
#include <NavalCommand/Error/Api/Result.h>
#include <gtest/gtest.h>
#include <variant>

enum class ProviderFailure
{
	Blocked
};

namespace ErrorApi = NavalCommand::Error::Api;

TEST(ResultTest, RepresentsSuccessfulAndGenericFailureResults)
{
	NavalCommand::Error::Api::Result<int> success{42};
	const auto failure = NavalCommand::Error::Api::MakeError(
		NavalCommand::Error::Api::ErrorCondition::NotReady);
	NavalCommand::Error::Api::Result<int> genericFailure{std::unexpected{failure}};

	ASSERT_TRUE(success.has_value());
	EXPECT_EQ(*success, 42);
	ASSERT_FALSE(genericFailure.has_value());
	EXPECT_EQ(genericFailure.error().Condition,
		NavalCommand::Error::Api::ErrorCondition::NotReady);
}

TEST(ResultTest, KeepsDomainFailuresInTheDomainErrorAlternative)
{
	using Failure = ErrorApi::CombinedError<ProviderFailure>;
	ErrorApi::DomainResult<int, ProviderFailure> result{
		std::unexpected{Failure{std::in_place_type<ProviderFailure>, ProviderFailure::Blocked}}};

	ASSERT_FALSE(result.has_value());
	EXPECT_TRUE(std::holds_alternative<ProviderFailure>(result.error()));
}
