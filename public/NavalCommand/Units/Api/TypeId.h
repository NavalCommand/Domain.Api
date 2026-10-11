#pragma once
#include <string>

namespace NavalCommand::Units::Api
{
	struct TypeId
	{
		std::string Value;
		bool operator==(const TypeId&) const = default;
	};
}
