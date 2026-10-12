#pragma once

#include <NavalCommand/Equipment/Api/IProvider.h>
#include <gmock/gmock.h>

namespace NavalCommand::Equipment::Api
{
	class IProviderMock : public IProvider
	{
	public:
		MOCK_METHOD((NavalCommand::Error::Api::DomainResult<Type, Error>),
			GetEquipmentType, (const TypeId& typeId), (const, override));
		MOCK_METHOD((NavalCommand::Error::Api::Result<std::vector<TypeId>>),
			GetEquipmentTypes, (), (override));
	};
}
