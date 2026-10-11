#pragma once
#include <variant>
#include <NavalCommand/Catalog/Api/EquipmentOperation.h>
#include <../../Equipment/Api/EquipmentTypeId.h>
#include <NavalCommand/Observations/Api/Id.h>
#include <NavalCommand/Observations/Api/Position.h>
#include <NavalCommand/Physics/Api/Position.h>
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
		std::variant<std::monostate, Observations::Api::Id, Physics::Api::Position, Physics::Api::Radians> Target;
		Catalog::Api::EquipmentTypeId EquipmentType;
	};

	struct EvasiveManeuvers
	{
		Uncertainty::Api::Exact<Observations::Api::Id> DangerSource;
	};

	using Activity = std::variant<std::monostate, Idle, MovingToWaypoint, EngagingWith, EvasiveManeuvers>;
}
