#pragma once
#include <NavalCommand/Catalog/Api/ResourceId.h>
#include <NavalCommand/Catalog/Api/ResourceValue.h>

namespace NavalCommand::Catalog::Api
{
	struct ResourceQuantity
	{
		ResourceId Resource;
		ResourceValue Amount;
	};
}
