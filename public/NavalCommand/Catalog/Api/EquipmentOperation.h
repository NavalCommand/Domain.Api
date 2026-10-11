#pragma once
#include <NavalCommand/Catalog/Api/ResourceQuantity.h>
#include <string>
#include <vector>

namespace NavalCommand::Catalog::Api
{
	struct EquipmentOperation
	{
		enum class TargetInput
		{
			Unit,
			Location,
			Area,
			Bearing
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

		struct ResourceCost
		{
			ResourceQuantity Quantity;
			ResourceUse Use{};
		};

		std::string Id;
		// Empty means no designation. Otherwise one of these designation kinds is accepted.
		std::vector<TargetInput> AcceptedTargets;
		Action Invocation{};
		// Consume depletes inventory per use; Reserve occupies capacity while active.
		std::vector<ResourceCost> Costs;
	};
}
