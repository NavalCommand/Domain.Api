#include <NavalCommand/Resources/Api/Definition.h>
#include <NavalCommand/Resources/Api/IProvider.h>
#include <NavalCommand/Resources/Api/Value.h>
#include <cstdint>
#include <type_traits>
#include <variant>

namespace Resources = NavalCommand::Resources::Api;

static_assert(std::is_abstract_v<Resources::IProvider>);
static_assert(std::variant_size_v<Resources::Value> == 2);

int main()
{
	Resources::Definition missiles;
	missiles.Id = {"missile-rounds"};
	missiles.Representation = Resources::Definition::NumericRepresentation::Discrete;
	missiles.Unit = Resources::Definition::MeasurementUnit::Count;
	missiles.Accounting = Resources::Definition::AccountingSemantics::Consumable;

	Resources::Value inventory = std::uint64_t{0};
	Resources::Value fuel = 0.3;
	return missiles.Id.Value == "missile-rounds" &&
		std::holds_alternative<std::uint64_t>(inventory) &&
	std::get<std::uint64_t>(inventory) == 0 && std::get<double>(fuel) == 0.3 ? 0 : 1;
}
