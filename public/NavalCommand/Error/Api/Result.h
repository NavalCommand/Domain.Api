#pragma once

#include <expected>

#include <NavalCommand/Error/Api/Error.h>

namespace NavalCommand::Error::Api
{
	template<typename T>
	using Result = std::expected<T, Error>;

	template<typename T, typename DomainError>
	using DomainResult =
		std::expected<T, CombinedError<DomainError>>;
}
