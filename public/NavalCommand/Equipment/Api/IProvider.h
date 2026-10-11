#pragma once

#include <expected>
#include <vector>
#include <NavalCommand/Equipment/Api/Type.h>
#include <NavalCommand/Equipment/Api/Error.h>

namespace NavalCommand::Equipment::Api
{
	class IProvider
	{
	public:
		virtual ~IProvider() = default;

		virtual std::expected<Type, Error> GetEquipmentType(const TypeId& typeId) const = 0;
		virtual std::vector<TypeId> GetEquipmentTypes() = 0;
	};

}
