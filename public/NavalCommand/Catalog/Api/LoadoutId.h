#pragma once
#include <string>

namespace NavalCommand::Catalog::Api
{
	struct LoadoutId
	{
		std::string Value;
		bool operator==(const LoadoutId&) const = default;
	};
}
