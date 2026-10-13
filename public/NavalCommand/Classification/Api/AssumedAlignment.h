#pragma once

namespace NavalCommand::Classification::Api
{
	// NATO APP-06(E), Section 1.2.1(a)(1), Table 1-1:
	// https://nso.nato.int/nso/nsdd/main/standards?search=NATO%20JOINT%20MILITARY%20SYMBOLOGY
	// NATO defines Assumed Friend and Suspect, but not Assumed Neutral.
	enum class AssumedAlignment
	{
		Friendly,
		Hostile
	};
}
