#pragma once
#include <expected>
#include <NavalCommand/Error/Api/Result.h>
#include <NavalCommand/Simulation/Api/Error.h>
#include <NavalCommand/Simulation/Api/TimeCompressionFactor.h>

namespace NavalCommand::Simulation::Api
{
	class ITimeCompressionProvider
	{
	public:
		virtual ~ITimeCompressionProvider() = default;

		virtual NavalCommand::Error::Api::DomainResult<void, Error> SetTimeCompression(TimeCompressionFactor factor) = 0;
	};

}
