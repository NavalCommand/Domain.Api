#include <NavalCommand/Uncertainty/Api/Knowledge.h>
#include <NavalCommand/Uncertainty/Api/ObservedCollection.h>
#include <cstdint>
#include <stdexcept>

namespace Uncertainty = NavalCommand::Uncertainty::Api;

static void Require(bool condition)
{
	if (!condition)
	{
		throw std::runtime_error("Uncertainty boundary assertion failed");
	}
}

int main()
{
	using Collection = Uncertainty::ObservedCollection<std::uint32_t>;
	Require(Collection{}.GetCoverage() == Collection::Coverage::Unknown);
	Require(Collection{Collection::Coverage::Complete, {}}.Items().empty());
	Require(Collection{Collection::Coverage::Partial, {}}.GetCoverage() == Collection::Coverage::Partial);
	Require(Collection{Collection::Coverage::Partial, {0}}.Items()[0] == 0);
	for (const auto invalidCoverage : {Collection::Coverage::Unknown, static_cast<Collection::Coverage>(99)})
	{
		bool rejected = false;
		try
		{
			Collection invalid{invalidCoverage, {0}};
		}
		catch (const std::invalid_argument&)
		{
			rejected = true;
		}
		Require(rejected);
	}

	Require(!Uncertainty::Knowledge<std::uint32_t>{}.HasValue());
	Require(Uncertainty::Knowledge<std::uint32_t>::Known(0).Value() == 0);
	Require(!Uncertainty::Knowledge<bool>::Known(false).Value());
	const auto estimated = Uncertainty::Knowledge<std::uint32_t>::Estimated(0, "observer evidence trace");
	Require(estimated.IsEstimated() && !estimated.IsKnown());
	Require(estimated.Value() == 0 && estimated.Source() == "observer evidence trace");
	Require(Uncertainty::Knowledge<bool>::Known(false).Source().empty());
	bool unknownRejected = false;
	try
	{
		Uncertainty::Knowledge<bool>{}.Value();
	}
	catch (const std::logic_error&)
	{
		unknownRejected = true;
	}
	Require(unknownRejected);
	return 0;
}
