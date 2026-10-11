#pragma once
#include <string>

namespace NavalCommand::Equipment::Api
{
	struct TypeId
	{
		std::string Value;
		bool operator==(const TypeId&) const = default;
	};
}
