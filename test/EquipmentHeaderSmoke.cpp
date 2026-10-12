#include <NavalCommand/Equipment/Api/Fit.h>
#include <NavalCommand/Equipment/Api/Instance.h>
#include <NavalCommand/Equipment/Api/IProvider.h>
#include <NavalCommand/Equipment/Api/Loadout.h>
#include <NavalCommand/Equipment/Api/Type.h>
#include <NavalCommand/Resources/Api/Value.h>
#include <cstdint>
#include <type_traits>
#include <variant>

namespace Equipment = NavalCommand::Equipment::Api;

static_assert(std::is_abstract_v<Equipment::IProvider>);
static_assert(!std::is_same_v<Equipment::TypeId, Equipment::LoadoutId>);

int main()
{
	Equipment::Fit fuelTank;
	fuelTank.TypeId = {"external-tank"};
	fuelTank.ResourceId = {"fuel"};
	fuelTank.ResourceCapacity = std::uint64_t{300};
	fuelTank.InitialInventory = std::uint64_t{120};

	Equipment::Loadout patrol;
	patrol.Id = {"patrol"};
	patrol.Equipment.push_back(fuelTank);

	Equipment::Type type;
	type.Id = fuelTank.TypeId;
	Equipment::Instance installed;
	installed.Type = type.Id;
	installed.State = Equipment::OperationalState::Ready;
	installed.DamageState = Equipment::Damage::Intact;
	installed.ExpendableResourceId = fuelTank.ResourceId;
	installed.ExpendableResourceValue = std::uint64_t{120};

	return patrol.Equipment.size() == 1 && patrol.Equipment.front().TypeId == type.Id &&
		std::get<std::uint64_t>(installed.ExpendableResourceValue) == 120 ? 0 : 1;
}
