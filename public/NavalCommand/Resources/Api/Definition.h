#pragma once
#include <NavalCommand/Resources/Api/Id.h>

namespace NavalCommand::Resources::Api
{
	struct Definition
	{
		enum class NumericRepresentation
		{
			Discrete,
			Continuous
		};

		enum class MeasurementUnit
		{
			Count,
			Kilograms,
			CubicMeters
		};

		enum class AccountingSemantics
		{
			Consumable,
			Allocatable
		};

		Id Id;
		NumericRepresentation Representation{};
		MeasurementUnit Unit{};
		AccountingSemantics Accounting{};
	};
}
