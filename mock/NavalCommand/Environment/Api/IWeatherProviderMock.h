#pragma once

#include <NavalCommand/Environment/Api/IWeatherProvider.h>

namespace NavalCommand::Environment::Api
{
	class IWeatherProviderMock final : public IWeatherProvider
	{
	};
}
