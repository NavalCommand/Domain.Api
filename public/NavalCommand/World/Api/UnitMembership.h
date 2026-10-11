#pragma once
#include <NavalCommand/Uncertainty/Api/Knowledge.h>
#include <NavalCommand/Units/Api/UnitId.h>
#include <string>

namespace NavalCommand::World::Api
{
	struct UnitMembership
	{
		Units::Api::UnitId Unit;
		// Observer-visible relationship IDs only; unknown enemy affiliation must remain unknown.
		Uncertainty::Api::Knowledge<std::string> Faction;
		Uncertainty::Api::Knowledge<std::string> TaskForce;
	};
}
