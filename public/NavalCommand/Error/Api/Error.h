#pragma once

#include <expected>
#include <system_error>
#include <variant>

#include "NavalCommand/Error/Api/ErrorCondition.h"

namespace NavalCommand::Error::Api
{
	struct Error
	{
		// Domain-agnostic error classification
		ErrorCondition Condition{};

		// Domain-specific cause
		std::error_code Cause{};

		[[nodiscard]] bool HasCause() const noexcept
		{
			return static_cast<bool>(Cause);
		}

		[[nodiscard]] bool operator==(const Error&) const = default;
	};

	template<typename DomainError>
	using CombinedError = std::variant<Error, DomainError>;

}
