#pragma once
#include <NavalCommand/World/Api/ResourceQuantity.h>
#include <cstddef>
#include <string>
#include <vector>

namespace NavalCommand::World::Api
{
	struct EquipmentOperation
	{
		enum class TargetInput
		{
			None,
			Track,
			Location,
			Area,
			Bearing
		};

		enum class Action
		{
			Launch,
			Deploy,
			Activate,
			Deactivate,
			Jettison
		};

		enum class Duration
		{
			OneShot,
			Continuous
		};

		std::string Id;
		std::size_t CapabilityIndex;
		std::vector<TargetInput> AcceptedTargets;
		Action Invocation;
		Duration OperationDuration;
		// Costs are consumed for one-shot operations, occupied while continuous operations run.
		std::vector<ResourceQuantity> Costs;

		enum class Mode
		{
			Active,
			Passive,
			Guided
		};

		std::vector<Mode> SupportedModes;
	};
}
