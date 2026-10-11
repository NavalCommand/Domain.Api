#pragma once

#include <expected>
#include <NavalCommand/Units/Api/Instance.h>
#include <NavalCommand/Units/Api/Error.h>

namespace NavalCommand::Units::Api
{
	class IProvider
	{
	public:
		virtual ~IProvider() = default;

		virtual std::vector<Id> GetUnitInstanceIds() const = 0;
		virtual std::expected<Instance, Error> GetUnitInstance(const Id& unitInstanceId) const = 0;
		virtual std::vector<TypeId> GetUnitTypes() = 0;
	};

}
