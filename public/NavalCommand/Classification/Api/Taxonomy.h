#pragma once

#include <NavalCommand/Classification/Api/Category.h>
#include <NavalCommand/Classification/Api/Dimension.h>
#include <NavalCommand/Classification/Api/SubCategory.h>
#include <optional>

namespace NavalCommand::Classification::Api
{
	// Dimension and category are derived from the most specific known classification.
	// Do not store independent values that can contradict this hierarchy.
	constexpr std::optional<Dimension> GetDimension(Category category) noexcept
	{
		switch (category)
		{
		case Category::Aircraft:
		case Category::Missile:
			return Dimension::Air;
		case Category::SurfaceVessel:
			return Dimension::SeaSurface;
		case Category::Submarine:
		case Category::Torpedo:
		case Category::Mine:
			return Dimension::SeaSubsurface;
		case Category::LandEquipment:
		case Category::LandInstallation:
		case Category::LandUnit:
			return Dimension::Land;
		case Category::SpaceObject:
			return Dimension::Space;
		}

		return std::nullopt;
	}

	constexpr std::optional<Category> GetCategory(SubCategory subCategory) noexcept
	{
		switch (subCategory)
		{
		case SubCategory::FixedWingAircraft:
		case SubCategory::RotaryWingAircraft:
		case SubCategory::TiltRotorAircraft:
			return Category::Aircraft;
		case SubCategory::CruiseMissile:
		case SubCategory::BallisticMissile:
			return Category::Missile;
		case SubCategory::AircraftCarrier:
		case SubCategory::Cruiser:
		case SubCategory::Destroyer:
		case SubCategory::Frigate:
		case SubCategory::Corvette:
		case SubCategory::PatrolVessel:
		case SubCategory::AmphibiousVessel:
		case SubCategory::AuxiliaryVessel:
		case SubCategory::MerchantVessel:
			return Category::SurfaceVessel;
		case SubCategory::AttackSubmarine:
		case SubCategory::BallisticMissileSubmarine:
		case SubCategory::CruiseMissileSubmarine:
			return Category::Submarine;
		case SubCategory::HeavyweightTorpedo:
		case SubCategory::LightweightTorpedo:
			return Category::Torpedo;
		case SubCategory::NavalMine:
			return Category::Mine;
		case SubCategory::GroundVehicle:
		case SubCategory::SurfaceToAirMissileLauncher:
		case SubCategory::AntiAircraftGun:
		case SubCategory::Radar:
			return Category::LandEquipment;
		case SubCategory::Airfield:
		case SubCategory::MilitaryInstallation:
		case SubCategory::CivilianInstallation:
			return Category::LandInstallation;
		}

		return std::nullopt;
	}

	constexpr bool IsConsistent(Category category, SubCategory subCategory) noexcept
	{
		return GetCategory(subCategory) == category;
	}
}
