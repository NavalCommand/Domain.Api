#pragma once
#include <variant>

namespace NavalCommand::World::Api
{
	struct EquipmentCapability
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
			SensingMode Mode;
		};

		struct Damage
		{
		};

		struct Jamming
		{
		};

		struct Deception
		{
		};

		struct Communication
		{
		};

		struct Storage
		{
		};

		std::variant<Sensing, Damage, Jamming, Deception, Communication, Storage> Behavior;
	};
}
