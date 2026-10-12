#pragma once

#include <expected>
#include <vector>
#include <NavalCommand/Error/Api/Result.h>
#include <NavalCommand/Resources/Api/Id.h>
#include <NavalCommand/Resources/Api/Definition.h>

namespace NavalCommand::Resources::Api
{
	class IProvider
	{
	public:
		virtual ~IProvider() = default;

		virtual Error::Api::Result<std::vector<Id>> GetResourceIds() const = 0;
		virtual Error::Api::Result<std::vector<Definition>> GetResourceDefinition(const Id& id) const = 0;
	};

}
