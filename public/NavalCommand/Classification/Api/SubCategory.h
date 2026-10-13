#pragma once

#include <NavalCommand/Classification/Api/Category.h>
#include <utility>

namespace NavalCommand::Classification::Api
{
	enum class SubCategory
	{
		// Aircraft
		FixedWingAircraft,
		RotaryWingAircraft,
		TiltRotorAircraft,

		// Missiles
		CruiseMissile,
		BallisticMissile,

		// Surface vessels
		AircraftCarrier,
		Cruiser,
		Destroyer,
		Frigate,
		Corvette,
		PatrolVessel,
		AmphibiousVessel,
		AuxiliaryVessel,
		MerchantVessel,

		// Submarines
		AttackSubmarine,
		BallisticMissileSubmarine,
		CruiseMissileSubmarine,

		// Underwater weapons
		HeavyweightTorpedo,
		LightweightTorpedo,
		NavalMine,

		// Naval devices
		Noisemaker,
		SelfPropelledAcousticDecoy,
		Sonobuoy,

		// Land equipment
		GroundVehicle,
		SurfaceToAirMissileLauncher,
		AntiAircraftGun,
		Radar,

		// Land installations
		Airfield,
		MilitaryInstallation,
		CivilianInstallation,

		// Generic fallback subcategories; appended to preserve existing enum values.
		Missile,
		Torpedo,
		SurfaceVessel,
		Submarine
	};

	// Every declared subcategory belongs to exactly one category.
	constexpr Category GetCategory(SubCategory subCategory) noexcept
	{
		switch (subCategory)
		{
		case SubCategory::FixedWingAircraft:
		case SubCategory::RotaryWingAircraft:
		case SubCategory::TiltRotorAircraft:
			return Category::Aircraft;
		case SubCategory::CruiseMissile:
		case SubCategory::BallisticMissile:
		case SubCategory::Missile:
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
		case SubCategory::SurfaceVessel:
			return Category::SurfaceVessel;
		case SubCategory::AttackSubmarine:
		case SubCategory::BallisticMissileSubmarine:
		case SubCategory::CruiseMissileSubmarine:
		case SubCategory::Submarine:
			return Category::Submarine;
		case SubCategory::HeavyweightTorpedo:
		case SubCategory::LightweightTorpedo:
		case SubCategory::Torpedo:
			return Category::Torpedo;
		case SubCategory::NavalMine:
			return Category::Mine;
		case SubCategory::Noisemaker:
		case SubCategory::SelfPropelledAcousticDecoy:
			return Category::SubsurfaceDevice;
		case SubCategory::Sonobuoy:
			return Category::SurfaceDevice;
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

		// Callers must provide a declared enum value; reject invalid wire codes at the boundary.
		std::unreachable();
	}
}
