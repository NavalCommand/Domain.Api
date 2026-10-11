#pragma once
#include <stdexcept>
#include <string>
#include <utility>
#include <variant>

namespace NavalCommand::Uncertainty::Api
{
	template <class T>
	class Knowledge
	{
		struct KnownValue
		{
			T Value;
		};

		struct EstimatedValue
		{
			T Value;
			std::string Source;
		};

		std::variant<std::monostate, KnownValue, EstimatedValue> m_State;

	public:
		static Knowledge Known(T value)
		{
			Knowledge result;
			result.m_State = KnownValue{std::move(value)};
			return result;
		}

		static Knowledge Estimated(T value, std::string source)
		{
			Knowledge result;
			result.m_State = EstimatedValue{std::move(value), std::move(source)};
			return result;
		}

		bool IsKnown() const
		{
			return m_State.index() == 1;
		}

		bool IsEstimated() const
		{
			return m_State.index() == 2;
		}

		bool HasValue() const
		{
			return m_State.index() != 0;
		}

		T& Value()
		{
			if (auto known = std::get_if<KnownValue>(&m_State))
			{
				return known->Value;
			}
			if (auto estimated = std::get_if<EstimatedValue>(&m_State))
			{
				return estimated->Value;
			}
			throw std::logic_error("Unknown knowledge has no value");
		}

		const T& Value() const
		{
			if (auto known = std::get_if<KnownValue>(&m_State))
			{
				return known->Value;
			}
			if (auto estimated = std::get_if<EstimatedValue>(&m_State))
			{
				return estimated->Value;
			}
			throw std::logic_error("Unknown knowledge has no value");
		}

		// Estimate trace, not necessarily a sensor identity or source class.
		const std::string& Source() const
		{
			if (auto estimated = std::get_if<EstimatedValue>(&m_State))
			{
				return estimated->Source;
			}
			static const std::string EMPTY_SOURCE;
			return EMPTY_SOURCE;
		}
	};
}
