#include <NavalCommand/Error/Api/MakeError.h>
#include <NavalCommand/Error/Api/Result.h>
#include <NavalCommand/Error/Api/ToStringView.h>
#include <expected>
#include <variant>

namespace Error = NavalCommand::Error::Api;

enum class ProviderFailure
{
	Blocked
};

int main()
{
	Error::Result<int> success{42};
	const Error::Error genericError = Error::MakeError(Error::ErrorCondition::NotReady);
	Error::Result<int> genericFailure{std::unexpected{genericError}};

	using CombinedFailure = Error::CombinedError<ProviderFailure>;
	Error::DomainResult<int, ProviderFailure> domainFailure{
		std::unexpected{CombinedFailure{std::in_place_type<ProviderFailure>, ProviderFailure::Blocked}}};

	return success.has_value() && *success == 42 && !genericFailure &&
		genericFailure.error().Condition == Error::ErrorCondition::NotReady &&
		!domainFailure && std::holds_alternative<ProviderFailure>(domainFailure.error()) &&
		Error::ToStringView(Error::ErrorCondition::NotReady) == "not ready" ? 0 : 1;
}
