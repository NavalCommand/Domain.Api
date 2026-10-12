#pragma once

#include <expected>
#include <vector>
#include <NavalCommand/Error/Api/Result.h>
#include <NavalCommand/Observations/Api/Id.h>
#include <NavalCommand/Observations/Api/Instance.h>

namespace NavalCommand::Observations::Api
{
	class IInstanceProvider
	{
	public:
		virtual ~IInstanceProvider() = default;

		virtual Error::Api::Result<std::vector<Id>> GetObservationIds() const = 0;
		virtual Error::Api::Result<Instance> GetObservationInstance(const Id& id) const = 0;
	};

}
