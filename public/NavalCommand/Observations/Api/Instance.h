#pragma once

#include <NavalCommand/Classification/Api/Category.h>
#include <NavalCommand/Classification/Api/Dimension.h>
#include <NavalCommand/Classification/Api/SubCategory.h>
#include <NavalCommand/Equipment/Api/LoadoutId.h>
#include <NavalCommand/Factions/Api/Id.h>
#include <NavalCommand/Observations/Api/Aircraft.h>
#include <NavalCommand/Observations/Api/Contributor.h>
#include <NavalCommand/Observations/Api/Id.h>
#include <NavalCommand/Observations/Api/Kinematics.h>
#include <NavalCommand/Uncertainty/Api/Exact.h>
#include <NavalCommand/Uncertainty/Api/Resolution.h>
#include <NavalCommand/Units/Api/TypeId.h>
#include <optional>
#include <string>
#include <vector>

namespace NavalCommand::Observations::Api
{
	struct Instance
	{
		Id Identity;
		std::string ObservationName; // Observer-facing name. Can be a track name or real unit name
		Factions::Api::Id ObserverFaction;
		Uncertainty::Api::Exact<Factions::Api::Id> ObservedFaction;

		// One most-specific observer-supported level, or Unknown.
		// Never resolve this from a hidden authoritative unit type.
		Uncertainty::Api::Resolution<
			Units::Api::TypeId,
			Classification::Api::SubCategory,
			Classification::Api::Category,
			Classification::Api::Dimension> Type;

		// Unknown, known absent, or known selected loadout.
		// Never infer this from hidden authoritative state.
		Uncertainty::Api::Exact<std::optional<Equipment::Api::LoadoutId>> CurrentLoadout;

		Kinematics Kinematics;
		std::optional<Aircraft> Aircraft;

		// Only source-supported attribution; empty means no contributors reported.
		std::vector<Contributor> Contributors;
	};
}
