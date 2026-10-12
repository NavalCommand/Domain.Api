#pragma once
#include <expected>
#include <NavalCommand/Error/Api/Result.h>

namespace NavalCommand::Simulation::Api
{
	class IPauseProvider
	{
	public:
		virtual ~IPauseProvider() = default;

		virtual NavalCommand::Error::Api::Result<bool> IsPaused() const = 0;
	};

}
