
#pragma once

#include <concepts>
#include <utility>
#include <variant>

namespace NavalCommand::Uncertainty::Api
{
	template<class... Levels>
	class Resolution
	{
	public:
		using Variant =
			std::variant<std::monostate, Levels...>;

		Resolution() = default;

		static Resolution Unknown()
		{
			return {};
		}

		template<class T>
			requires (std::same_as<T, Levels> || ...)
		static Resolution Known(T value)
		{
			Resolution result;
			result.m_Value.template emplace<T>(
				std::move(value));
			return result;
		}

		bool IsKnown() const noexcept
		{
			return !IsUnknown();
		}

		bool IsUnknown() const noexcept
		{
			return std::holds_alternative<
				std::monostate>(m_Value);
		}

		template<class T>
		const T* GetIf() const noexcept
		{
			return std::get_if<T>(&m_Value);
		}

		const Variant& Value() const noexcept
		{
			return m_Value;
		}

	private:
		Variant m_Value{};
	};
}
