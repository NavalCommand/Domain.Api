#pragma once

#include <NavalCommand/Error/Api/Result.h>
#include <NavalCommand/Simulation/Api/TimeCompressionFactor.h>

namespace NavalCommand::Simulation::Api
{
	class ITimeCompressionProvider
	{
	public:
		virtual ~ITimeCompressionProvider() = default;

		virtual Error::Api::Result<TimeCompressionFactor> GetTimeCompression() = 0;
	};

}
