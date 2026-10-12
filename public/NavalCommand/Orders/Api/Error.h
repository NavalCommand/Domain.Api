#pragma once

namespace NavalCommand::Orders::Api
{
	enum class Error
	{
		Unknown,
		TemporarilyBlocked,
		Unsupported,
		InvalidRequest,
		Interrupted
	};
}
