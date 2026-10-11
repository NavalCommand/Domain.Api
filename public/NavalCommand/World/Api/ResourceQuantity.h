#pragma once
#include <cstdint>

namespace NavalCommand::World::Api {
struct ResourceQuantity {
	enum class Kind {
		Ammunition,
		DeploymentCharges,
		JamChannels,
		FuelLiters
	};
	Kind Resource;
	double Amount;
};
}
