#include <NavalCommand/Environment/Api/Error.h>
#include <NavalCommand/Environment/Api/ITimeProvider.h>
#include <NavalCommand/Environment/Api/ITerrainInfoProvider.h>
#include <NavalCommand/Environment/Api/IWeatherProvider.h>
#include <NavalCommand/Environment/Api/TerrainType.h>
#include <type_traits>

namespace Environment = NavalCommand::Environment::Api;

static_assert(std::is_abstract_v<Environment::IProvider>);
static_assert(std::is_abstract_v<Environment::ITimeProvider>);
static_assert(std::is_default_constructible_v<Environment::IWeatherProvider>);

int main()
{
	const auto terrain = Environment::TerrainType::Water;
	const auto failure = Environment::Error::InvalidCoordinates;
	return terrain == Environment::TerrainType::Water &&
		failure == Environment::Error::InvalidCoordinates ? 0 : 1;
}
