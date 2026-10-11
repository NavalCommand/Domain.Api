#pragma once
#include <NavalCommand/World/Api/ObservationAssociation.h>
#include <NavalCommand/World/Api/ObserverSnapshot.h>
#include <NavalCommand/World/Api/SimulationSnapshot.h>
#include <vector>

namespace NavalCommand::World::Api
{
	// Privileged in-memory capture only; snapshots do not claim deterministic replay.
	struct RecordedSnapshots
	{
		SimulationSnapshot Truth;
		std::vector<ObserverSnapshot> Perspectives;
		std::vector<ObservationAssociation> Associations;
	};
}
