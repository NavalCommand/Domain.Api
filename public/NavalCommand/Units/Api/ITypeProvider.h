#pragma once

#include <expected>
#include <NavalCommand/Error/Api/Result.h>
#include <NavalCommand/Units/Api/Instance.h>

namespace NavalCommand::Units::Api
{
	class ITypeProvider
	{
	public:
		virtual ~ITypeProvider() = default;

		virtual Error::Api::Result<std::vector<TypeId>> GetUnitTypes() = 0;
	};

}
