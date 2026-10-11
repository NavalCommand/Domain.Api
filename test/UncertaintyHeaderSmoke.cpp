#include <NavalCommand/Uncertainty/Api/Exact.h>
#include <cstdint>
#include <stdexcept>

namespace Uncertainty = NavalCommand::Uncertainty::Api;

static void Require(bool condition)
{
	if (!condition)
	{
		throw std::runtime_error("Exact boundary assertion failed");
	}
}

int main()
{
	Require(!Uncertainty::Exact<std::uint32_t>{}.HasValue());
	Require(!Uncertainty::Exact<std::uint32_t>::Unknown().IsKnown());
	Require(Uncertainty::Exact<std::uint32_t>::Known(0).Value() == 0);
	Require(!Uncertainty::Exact<bool>::Known(false).Value());
	return 0;
}
