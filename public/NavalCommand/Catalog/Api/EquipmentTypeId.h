#pragma once
#include <string>

namespace NavalCommand::Catalog::Api
{
	struct EquipmentTypeId
	{
		std::string Value;
		bool operator==(const EquipmentTypeId&) const = default;
	};
}
