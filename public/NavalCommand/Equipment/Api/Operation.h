#pragma once
#include <cstdint>
#include <NavalCommand/Resources/Api/Id.h>
#include <NavalCommand/Resources/Api/Value.h>
#include <optional>

namespace NavalCommand::Equipment::Api
{
	struct Operation
	{
		enum class TargetInput : std::uint8_t
		{
			NoTarget = (1 << 0),
			Unit = (1 << 1),
			Location = (1 << 2),
			Bearing = (1 << 3),
		};

		enum class Action
		{
			Use,
			SetActive
		};

		enum class ResourceUse
		{
			Consume,
			Reserve
		};

		struct ResourceRequirement
		{
			ResourceUse Use;
			Resources::Api::Id ResourceId;
			Resources::Api::Value Amount;
		};

		TargetInput AcceptedTargets;
		Action Invocation{};

		// Absence means the operation neither consumes nor reserves a resource.
		std::optional<ResourceRequirement> Resource;
	};
}
