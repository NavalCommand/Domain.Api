#pragma once
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

namespace NavalCommand::Uncertainty::Api
{
	template <class T>
	class ObservedCollection
	{
	public:
		enum class Coverage
		{
			Unknown,
			Partial,
			Complete
		};

	private:
		Coverage m_Coverage = Coverage::Unknown;
		std::vector<T> m_Items;

	public:
		ObservedCollection() = default;

		ObservedCollection(Coverage coverage, std::vector<T> items) : m_Coverage{coverage}, m_Items{std::move(items)}
		{
			if (coverage != Coverage::Unknown && coverage != Coverage::Partial && coverage != Coverage::Complete)
			{
				throw std::invalid_argument("Invalid collection coverage");
			}
			if (coverage == Coverage::Unknown && !m_Items.empty())
			{
				throw std::invalid_argument("Unknown collection cannot contain items");
			}
		}

		Coverage GetCoverage() const
		{
			return m_Coverage;
		}

		const std::vector<T>& Items() const
		{
			return m_Items;
		}

		T& At(std::size_t index)
		{
			return m_Items.at(index);
		}

		// Partial + empty means incomplete enumeration without reportable members.
	};
}
