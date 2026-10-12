#pragma once

#include <system_error>

#include "NavalCommand/Error/Api/Error.h"

namespace NavalCommand::Error::Api
{
	[[nodiscard]] inline Error MakeError(const ErrorCondition condition) noexcept
	{
		return Error{condition, {}};
	}

	[[nodiscard]] inline Error MakeError(const ErrorCondition condition, const std::error_code cause) noexcept
	{
		return Error{condition, cause};
	}
}
