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

		virtual NavalCommand::Error::Api::Result<bool> CanPause() const = 0;
		virtual NavalCommand::Error::Api::Result<bool> CanUnpause() const = 0;
		virtual NavalCommand::Error::Api::DomainResult<void, Error> SetPause(bool paused) = 0;
	};

}
