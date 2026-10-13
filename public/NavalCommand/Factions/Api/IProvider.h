#pragma once

#include <NavalCommand/Classification/Api/Alignment.h>
#include <NavalCommand/Error/Api/Result.h>
#include <NavalCommand/Factions/Api/Error.h>
#include <NavalCommand/Factions/Api/Id.h>
#include <vector>

namespace NavalCommand::Factions::Api
{
	class IProvider
	{
	public:
		virtual ~IProvider() = default;

		virtual Error::Api::Result<std::vector<Id>> GetFactionIds() = 0;
		virtual Error::Api::DomainResult<Classification::Api::Alignment, Error> GetFactionAlignment(
			const Id& faction1, const Id& faction2) = 0;
	};
}
