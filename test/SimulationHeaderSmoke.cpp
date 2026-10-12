#include <NavalCommand/Simulation/Api/Error.h>
#include <NavalCommand/Simulation/Api/IPauseController.h>
#include <NavalCommand/Simulation/Api/IPauseProvider.h>
#include <NavalCommand/Simulation/Api/ITimeCompressionController.h>
#include <NavalCommand/Simulation/Api/ITimeCompressionProvider.h>
#include <NavalCommand/Simulation/Api/TimeCompressionFactor.h>
#include <type_traits>

namespace Simulation = NavalCommand::Simulation::Api;

static_assert(std::is_abstract_v<Simulation::IPauseController>);
static_assert(std::is_abstract_v<Simulation::IPauseProvider>);
static_assert(std::is_abstract_v<Simulation::ITimeCompressionController>);
static_assert(std::is_abstract_v<Simulation::ITimeCompressionProvider>);

int main()
{
	const Simulation::TimeCompressionFactor factor{4.0};
	const auto failure = Simulation::Error::Blocked;
	return factor == Simulation::TimeCompressionFactor{4.0} &&
		failure == Simulation::Error::Blocked ? 0 : 1;
}
