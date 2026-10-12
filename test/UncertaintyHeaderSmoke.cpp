#include <NavalCommand/Uncertainty/Api/Exact.h>
#include <NavalCommand/Uncertainty/Api/Resolution.h>
#include <cstdint>
#include <stdexcept>
#include <string>

namespace Uncertainty = NavalCommand::Uncertainty::Api;

static void Require(bool condition)
{
	if (!condition)
	{
		throw std::runtime_error("Uncertainty semantic assertion failed");
	}
}

int main()
{
	const auto unknown = Uncertainty::Exact<std::uint32_t>::Unknown();
	const auto knownZero = Uncertainty::Exact<std::uint32_t>::Known(0);
	const auto knownFalse = Uncertainty::Exact<bool>::Known(false);
	Require(!unknown.HasValue() && !unknown.IsKnown());
	Require(knownZero.IsKnown() && knownZero.Value() == 0);
	Require(knownFalse.HasValue() && !knownFalse.Value());

	using TypeResolution = Uncertainty::Resolution<std::uint32_t, std::string>;
	const auto unknownType = TypeResolution::Unknown();
	const auto resolvedNumber = TypeResolution::Known<std::uint32_t>(42);
	const auto resolvedLabel = TypeResolution::Known<std::string>("tracked");
	Require(unknownType.IsUnknown() && !unknownType.IsKnown());
	Require(resolvedNumber.IsKnown() && *resolvedNumber.GetIf<std::uint32_t>() == 42);
	Require(*resolvedLabel.GetIf<std::string>() == "tracked");
	return 0;
}
