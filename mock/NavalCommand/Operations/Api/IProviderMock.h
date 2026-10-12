#pragma once

#include <NavalCommand/Operations/Api/IProvider.h>
#include <gmock/gmock.h>

namespace NavalCommand::Operations::Api
{
	class IProviderMock : public IProvider
	{
	public:
		MOCK_METHOD((NavalCommand::Error::Api::Result<UnitState>),
			GetUnitOperations, (const Units::Api::Id& unitId), (const, override));
	};
}
