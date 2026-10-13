#pragma once

#include <NavalCommand/Classification/Api/Dimension.h>
#include <utility>

namespace NavalCommand::Classification::Api
{
	enum class Category
	{
		Aircraft,
		Missile,
		SurfaceVessel,
		Submarine,
		Torpedo,
		Mine,
		LandEquipment,
		LandInstallation,
		LandUnit,
		SpaceObject,
		SurfaceDevice,
		SubsurfaceDevice
	};

	// Every declared category has exactly one operational dimension.
	constexpr Dimension GetDimension(Category category) noexcept
	{
		switch (category)
		{
		case Category::Aircraft:
		case Category::Missile:
			return Dimension::Air;
		case Category::SurfaceVessel:
		case Category::SurfaceDevice:
			return Dimension::SeaSurface;
		case Category::Submarine:
		case Category::Torpedo:
		case Category::Mine:
		case Category::SubsurfaceDevice:
			return Dimension::SeaSubsurface;
		case Category::LandEquipment:
		case Category::LandInstallation:
		case Category::LandUnit:
			return Dimension::Land;
		case Category::SpaceObject:
			return Dimension::Space;
		}

		// Callers must provide a declared enum value; reject invalid wire codes at the boundary.
		std::unreachable();
	}
}
