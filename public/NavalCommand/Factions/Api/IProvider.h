#pragma once

#include <expected>
#include <vector>
#include <NavalCommand/Factions/Api/Alignment.h>
#include <NavalCommand/Factions/Api/Id.h>
#include <NavalCommand/Factions/Api/Error.h>

namespace NavalCommand::Factions::Api
{
	class IProvider
	{
	public:
		virtual ~IProvider() = default;

		virtual std::vector<Id> GetFactionIds() = 0;
		virtual std::expected<Alignment, Error> GetFactionAlignment(const Id& faction1, const Id& faction2) = 0;
	};

}
