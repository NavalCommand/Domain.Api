#pragma once
#include <cstdint>
#include <NavalCommand/Resources/Api/Id.h>
#include <NavalCommand/Resources/Api/Value.h>

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

		TargetInput AcceptedTargets;
		Action Invocation{};

		ResourceUse CostResourceUse;
		Resources::Api::Id CostResource;
		Resources::Api::Value CostAmount;
	};
}
