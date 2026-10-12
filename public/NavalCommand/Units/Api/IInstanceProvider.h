#pragma once

#include <expected>
#include <NavalCommand/Error/Api/Result.h>
#include <NavalCommand/Units/Api/Instance.h>

namespace NavalCommand::Units::Api
{
	class IInstanceProvider
	{
	public:
		virtual ~IInstanceProvider() = default;

		virtual Error::Api::Result<std::vector<Id>> GetUnitInstanceIds() const = 0;
		virtual Error::Api::Result<Instance> GetUnitInstance(const Id& unitInstanceId) const = 0;
	};

}
