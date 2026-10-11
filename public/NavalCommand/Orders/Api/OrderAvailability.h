#pragma once
#include <NavalCommand/Orders/Api/Eligibility.h>
#include <NavalCommand/Uncertainty/Api/ObservedCollection.h>
#include <NavalCommand/Units/Api/UnitId.h>
#include <cstdint>

namespace NavalCommand::Orders::Api
{
	struct OrderAvailability
	{
		Units::Api::UnitId Unit;
		std::uint64_t BasedOnVersion{};
		Uncertainty::Api::ObservedCollection<Eligibility> Orders;
	};
}
