#pragma once
#include <cstdint>

namespace NavalCommand::World::Api
{
	struct ResourceQuantity
	{
		// TODO not sure if we need this much Kinds.
		// I am also not sure if we need to encode this much semantics into ResourceQuantity.
		// Equipment semantics can be inferred from other capabilities, ResourceQuantity has another purpose - encoding the depletion behavior.
		// It must encode "is it integer?", "is it double?", "is it allocatable instead of expandable?"
		enum class Kind
		{
			Ammunition,
			DeploymentCharges,
			JamChannels,
			FuelLiters
		};

		Kind Resource;
		double Amount;
	};
}
