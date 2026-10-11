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

		// TODO This enum encodes a lot of effectively equivalent semantics.
		// What is the difference between Launch, Deploy and Jettison?
		// From the program perspective these are the same capability - "Expend a resource to deliver an effect"
		// What really is a separate mode is Activation and Deactivation, because its expenditure semantics is different.
		// So, in my view, Action must have two values: "Use" and "Toggle"
		enum class Action
		{
			Launch,
			Deploy,
			Activate,
			Deactivate,
			Jettison
		};

		// TODO Duration can be deduced from Action. Activate and Deactivate implies Continuous duration, Launch implies OneShot.
		// This enum is probably not needed.
		enum class Duration
		{
			OneShot,
			Continuous
		};

		std::string Id;
		std::size_t CapabilityIndex; // TODO Index in what? Probably not needed. Especially if we already have Id.
		std::vector<TargetInput> AcceptedTargets;
		Action Invocation;
		Duration OperationDuration;
		// Costs are consumed for one-shot operations, occupied while continuous operations run.
		std::vector<ResourceQuantity> Costs;

		// TODO Not sure what this enum describes. If this is about type of seeker - it does not belong here. Type of seeker should probably be a separate metadata about a weapon, not part of EquipmentOperation.
		// If this is about whether the shooter requires active control over the projectile (like wire-guided torpedoes), then this Mode has wrong semantics.
		enum class Mode
		{
			Active,
			Passive,
			Guided
		};

		std::vector<Mode> SupportedModes;
	};
}
