#pragma once

#include <expected>
#include <NavalCommand/Error/Api/Result.h>
#include <NavalCommand/Units/Api/Instance.h>
#include <NavalCommand/Units/Api/Type.h>

namespace NavalCommand::Units::Api
{
	class ITypeProvider
	{
	public:
		virtual ~ITypeProvider() = default;

		virtual Error::Api::Result<std::vector<TypeId>> GetUnitTypeIds() = 0;
		virtual Error::Api::Result<Type> GetUnitType(const TypeId& typeId) = 0;
	};

}
