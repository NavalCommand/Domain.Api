#pragma once

#include <expected>
#include <NavalCommand/Catalog/Api/Catalog.h>

namespace NavalCommand::Resources::Api
{
	class IProvider
	{
	public:
		virtual ~IProvider() = default;

		virtual std::vector<Id> GetResourceIds() const = 0;
		virtual std::vector<Definition> GetResourceDefinition(const Id& id) const = 0;
	};

}