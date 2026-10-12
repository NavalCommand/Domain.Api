#pragma once
#include <NavalCommand/Error/Api/Result.h>
#include <NavalCommand/Operations/Api/UnitState.h>
#include <NavalCommand/Units/Api/Id.h>

namespace NavalCommand::Operations::Api
{
	class IProvider
	{
	public:
		virtual ~IProvider() = default;

		virtual NavalCommand::Error::Api::Result<UnitState> GetUnitOperations(
			const Units::Api::Id& unitId) const = 0;
	};
}
