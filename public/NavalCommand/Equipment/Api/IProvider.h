#pragma once

#include <expected>
#include <vector>
#include <NavalCommand/Equipment/Api/Type.h>
#include <NavalCommand/Equipment/Api/Error.h>
#include <NavalCommand/Error/Api/Result.h>

namespace NavalCommand::Equipment::Api
{
	class IProvider
	{
	public:
		virtual ~IProvider() = default;

		virtual NavalCommand::Error::Api::DomainResult<Type, Error> GetEquipmentType(const TypeId& typeId) const = 0;
		virtual NavalCommand::Error::Api::Result<std::vector<TypeId>> GetEquipmentTypes() = 0;
	};

}
