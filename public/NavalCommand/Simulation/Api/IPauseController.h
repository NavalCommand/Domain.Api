#pragma once
#include <expected>
#include <NavalCommand/Error/Api/Result.h>
#include <NavalCommand/Simulation/Api/Error.h>

namespace NavalCommand::Simulation::Api
{
	class IPauseController
	{
	public:
		virtual ~IPauseController() = default;

		virtual NavalCommand::Error::Api::Result<bool> CanRequestPause() const = 0;
		virtual NavalCommand::Error::Api::Result<bool> CanRequestUnpause() const = 0;
		virtual NavalCommand::Error::Api::DomainResult<void, Error> RequestPause(bool paused) = 0;
	};

}
