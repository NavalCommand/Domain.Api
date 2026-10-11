#pragma once
#include <string>

namespace NavalCommand::World::Api
{
	struct TaskForceId
	{
		std::string Value;
		bool operator==(const TaskForceId&) const = default;
	};
}
