#pragma once
#include <NavalCommand/Observations/Api/ObservationId.h>
#include <NavalCommand/Observations/Api/ObserverId.h>
#include <NavalCommand/Orders/Api/Eligibility.h>
#include <cstdint>
#include <vector>

namespace NavalCommand::Orders::Api
{
	struct OrderAvailability
	{
		Observations::Api::ObserverId Observer;
		Observations::Api::ObservationId Observation;
		std::uint64_t BasedOnVersion{};
		// A missing order row is not executable; consumers/providers must treat it as unreported.
		std::vector<Eligibility> Orders;
	};
}
