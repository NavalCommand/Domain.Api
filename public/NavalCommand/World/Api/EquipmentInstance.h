#pragma once
#include <NavalCommand/World/Api/Knowledge.h>
#include <NavalCommand/World/Api/PhysicalTraits.h>
#include <NavalCommand/World/Api/ResourceQuantity.h>
#include <optional>
#include <string>
#include <vector>

namespace NavalCommand::World::Api {
struct EquipmentInstance {
	enum class Readiness {
		Ready,
		Busy,
		Unavailable
	};
	enum class Damage {
		Intact,
		Damaged,
		Destroyed
	};
	struct Resource {
		ResourceQuantity::Kind Kind;
		Knowledge<double> Amount;
	};
	Knowledge<std::string> TypeId;
	Knowledge<bool> Active;
	Knowledge<Readiness> OperationalReadiness;
	Knowledge<Damage> DamageState;
	std::vector<Resource> Resources;
	std::optional<PhysicalTraits> Physical;
};
}
