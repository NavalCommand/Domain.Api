
#pragma once

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

		// Land equipment
		GroundVehicle,
		SurfaceToAirMissileLauncher,
		AntiAircraftGun,
		Radar,

		// Land installations
		Airfield,
		MilitaryInstallation,
		CivilianInstallation
	};
}
