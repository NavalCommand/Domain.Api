#pragma once
#include <NavalCommand/Catalog/Api/ResourceId.h>

namespace NavalCommand::Catalog::Api
{
	struct ResourceDefinition
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

		ResourceId Id;
		NumericRepresentation Representation{};
		MeasurementUnit Unit{};
		AccountingSemantics Accounting{};
	};
}
