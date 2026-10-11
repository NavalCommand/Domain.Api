#pragma once
#include <string>

namespace NavalCommand::Catalog::Api
{
	struct UnitTypeId
	{
		std::string Value;
		bool operator==(const UnitTypeId&) const = default;
	};
}
