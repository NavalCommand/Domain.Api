#pragma once

#include "NavalCommand/Classification/Api/Category.h"
#include "NavalCommand/Classification/Api/Dimension.h"

namespace NavalCommand::Classification::Api
{
	struct Taxonomy
	{
		Category UnitCategory;
		Dimension UnitDimension;
	};
}
