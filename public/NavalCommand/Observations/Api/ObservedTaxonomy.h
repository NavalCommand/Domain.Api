#pragma once

#include <NavalCommand/Uncertainty/Api/Exact.h>

#include "NavalCommand/Classification/Api/Category.h"
#include "NavalCommand/Classification/Api/Dimension.h"

namespace NavalCommand::Observations::Api
{
	struct ObservedTaxonomy
	{
		Uncertainty::Api::Exact<Classification::Api::Category> UnitCategory;
		Uncertainty::Api::Exact<Classification::Api::Dimension> UnitDimension;
	};
}
