#pragma once
#include <variant>
#include <NavalCommand/Equipment/Api/TypeId.h>
#include <NavalCommand/Physics/Api/Position.h>
#include <NavalCommand/Physics/Api/Radians.h>
#include <NavalCommand/Units/Api/Id.h>
#include <NavalCommand/Uncertainty/Api/Exact.h>

namespace NavalCommand::Units::Api
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
		std::variant<std::monostate, Id, Physics::Api::Position, Physics::Api::Radians> Target;
		Equipment::Api::TypeId EquipmentType;
	};

	struct EvasiveManeuvers
	{
		Uncertainty::Api::Exact<Id> DangerSource;
	};

	using Activity = std::variant<std::monostate, Idle, MovingToWaypoint, EngagingWith, EvasiveManeuvers>;
}
