#pragma once
#include <cstdint>
#include <variant>

namespace NavalCommand::Catalog::Api
{
	// Discrete values are exact counts. Continuous values are expressed in the definition's SI unit.
	using ResourceValue = std::variant<std::uint64_t, double>;
}
