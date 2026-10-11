#pragma once

namespace NavalCommand::Orders::Api
{
	enum class Failure
	{
		Unknown,
		TemporarilyBlocked,
		Unsupported,
		InvalidRequest,
		Interrupted
	};
}
