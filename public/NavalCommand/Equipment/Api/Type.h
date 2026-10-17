#pragma once
#include <NavalCommand/Equipment/Api/TypeId.h>
#include <vector>
#include <NavalCommand/Equipment/Api/Effect.h>
#include <NavalCommand/Equipment/Api/Operation.h>

namespace NavalCommand::Equipment::Api
{
	// One independently addressable operational capability, not necessarily one physical device.
	struct Type
	{
		TypeId Id;
		std::optional<std::string> DisplayName;
		std::optional<std::string> AlternativeDisplayName;
		std::vector<Equipment::Api::Effect> Effects;
		std::vector<Equipment::Api::Operation> Operations;
	};
}
