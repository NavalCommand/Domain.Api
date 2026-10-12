#pragma once
#include <NavalCommand/Error/Api/Result.h>
#include <NavalCommand/Physics/Api/Seconds.h>

namespace NavalCommand::Environment::Api
{
	class ITimeProvider
	{
	public:
		virtual ~ITimeProvider() = default;

		virtual Error::Api::Result<Physics::Api::Seconds> GetCurrentTime() = 0;
	};

}
