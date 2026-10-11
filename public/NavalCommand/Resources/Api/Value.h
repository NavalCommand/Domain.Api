#pragma once
#include <cstdint>
#include <variant>

namespace NavalCommand::Resources::Api
{
	// Discrete values are exact counts. Continuous values are expressed in the definition's SI unit.
	using Value = std::variant<std::uint64_t, double>;
}
