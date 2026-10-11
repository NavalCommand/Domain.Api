#pragma once
#include <NavalCommand/Observations/Api/ObservationId.h>
#include <NavalCommand/Observations/Api/ObserverId.h>
#include <NavalCommand/Orders/Api/Eligibility.h>
#include <NavalCommand/Uncertainty/Api/ObservedCollection.h>
#include <cstdint>

namespace NavalCommand::Orders::Api
{
	struct OrderAvailability
	{
		Observations::Api::ObserverId Observer;
		Observations::Api::ObservationId Observation;
		std::uint64_t BasedOnVersion{};
		Uncertainty::Api::ObservedCollection<Eligibility> Orders;
	};
}
