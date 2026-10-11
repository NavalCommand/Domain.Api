#pragma once
#include <NavalCommand/Physics/Api/Meters.h>
#include <optional>
#include <variant>

namespace NavalCommand::Catalog::Api
{
	struct EquipmentEffect
	{
		enum class SensingMode
		{
			Radar,
			Sonar,
			Esm,
			Visual
		};

		struct Sensing
		{
			SensingMode Mode{};
			// Intrinsic nominal constraint, not installation geometry or measured detection range.
			std::optional<Physics::Api::Meters> NominalRange;
		};

		struct Damage
		{
			enum class Guidance
			{
				Autonomous,
				Command
			};

			std::optional<Guidance> ProjectileGuidance;
		};

		struct Jamming {};
		struct Deception {};
		struct Communication {};
		struct Storage {};

		std::variant<Sensing, Damage, Jamming, Deception, Communication, Storage> Behavior;
	};
}
