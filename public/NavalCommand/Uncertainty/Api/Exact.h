#pragma once
#include <optional>
#include <utility>

namespace NavalCommand::Uncertainty::Api
{
	template <class T>
	class Exact
	{
		std::optional<T> m_Value;

	public:
		Exact() = default;

		static Exact Known(T value)
		{
			Exact result;
			result.m_Value.emplace(std::move(value));
			return result;
		}

		static Exact Unknown()
		{
			return {};
		}

		bool HasValue() const noexcept
		{
			return m_Value.has_value();
		}

		bool IsKnown() const noexcept
		{
			return HasValue();
		}

		T& Value()
		{
			return m_Value.value();
		}

		const T& Value() const
		{
			return m_Value.value();
		}
	};
}
