#include <NavalCommand/Factions/Api/Alignment.h>
#include <NavalCommand/Factions/Api/IProvider.h>
#include <NavalCommand/Factions/Api/Id.h>
#include <type_traits>

namespace Factions = NavalCommand::Factions::Api;

static_assert(std::is_abstract_v<Factions::IProvider>);

int main()
{
	const Factions::Id blue{"blue"};
	const Factions::Alignment relationship = Factions::Alignment::Friendly;
	return blue.Value == "blue" && relationship == Factions::Alignment::Friendly ? 0 : 1;
}
