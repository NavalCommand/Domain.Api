#pragma once

#include <NavalCommand/Units/Api/ITypeProvider.h>
#include <gmock/gmock.h>

namespace NavalCommand::Units::Api
{
	class ITypeProviderMock : public ITypeProvider
	{
	public:
		MOCK_METHOD((Error::Api::Result<std::vector<TypeId>>), GetUnitTypeIds, (), (override));
		MOCK_METHOD((Error::Api::Result<Type>), GetUnitType, (const TypeId& typeId), (override));
	};
}
