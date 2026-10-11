#pragma once
#include <NavalCommand/Orders/Api/Eligibility.h>
#include <NavalCommand/World/Api/ObservedCollection.h>

namespace NavalCommand::World::Api {
struct OrderEligibilityState {
	ObservedCollection<Orders::Api::Eligibility> Orders;
};
}
