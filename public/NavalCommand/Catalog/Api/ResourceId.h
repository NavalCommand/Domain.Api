#pragma once
#include <string>

namespace NavalCommand::Catalog::Api
{
	struct ResourceId
	{
		std::string Value;
		bool operator==(const ResourceId&) const = default;
	};
}
