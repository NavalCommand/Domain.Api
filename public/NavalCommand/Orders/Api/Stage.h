#pragma once

namespace NavalCommand::Orders::Api {
enum class Stage {
	Unknown,
	Received,
	Rejected,
	NativeTaskCreated,
	MovementObserved,
	RouteMutated,
	ExecutionUnknown,
	Preparing,
	AircraftSpawned,
	Airborne
};
} // namespace NavalCommand::Orders::Api
