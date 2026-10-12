#pragma once

#include <expected>
#include <vector>
#include <NavalCommand/Error/Api/Result.h>
#include <NavalCommand/Factions/Api/Alignment.h>
#include <NavalCommand/Factions/Api/Id.h>
#include <NavalCommand/Factions/Api/Error.h>

namespace NavalCommand::Factions::Api
{
	class IProvider
	{
	public:
		virtual ~IProvider() = default;

		virtual NavalCommand::Error::Api::Result<std::vector<Id>> GetFactionIds() = 0;
		virtual NavalCommand::Error::Api::DomainResult<Alignment, Error> GetFactionAlignment(const Id& faction1, const Id& faction2) = 0;
	};

}
