#pragma once
#include <NavalCommand/Equipment/Api/TypeId.h>
#include <NavalCommand/Observations/Api/Id.h>
#include <NavalCommand/Physics/Api/Position.h>
#include <NavalCommand/Physics/Api/Radians.h>
#include <NavalCommand/Uncertainty/Api/Exact.h>
#include <variant>

namespace NavalCommand::Operations::Api
{
	struct Idle
	{
	};

	struct MovingToWaypoint
	{
		Physics::Api::Position TargetPosition;
	};

	struct EngagingWith
	{
		std::variant<std::monostate, Observations::Api::Id, Physics::Api::Position, Physics::Api::Radians> Target;
		Equipment::Api::TypeId EquipmentType;
	};

	struct EvasiveManeuvers
	{
		Uncertainty::Api::Exact<Observations::Api::Id> DangerSource;
	};

	using Activity = std::variant<
		std::monostate,
		Idle,
		MovingToWaypoint,
		EngagingWith,
		EvasiveManeuvers>;
}
