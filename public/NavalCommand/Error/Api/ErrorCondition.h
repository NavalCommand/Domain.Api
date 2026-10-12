#pragma once

namespace NavalCommand::Error::Api
{
	// Domain-agnostic infrastructure error conditions. Do not use to describe Simulation-level errors, use domain-specific errors for Simulation errors.
	enum class ErrorCondition
	{
		ContractError,		// Caller did not respect pre-conditions imposed by the target API, e.g., argument was out of supported range
		CommunicationError,	// Network Transport error, e.g., server not responding
		DeviceError,		// Hardware error
		NotFound,			// Requested resource does not exist, e.g., invalid instance or type id
		NotReady,			// Callee temporarily cannot fulfill the contract, caller should try the same call again later.
		PermissionDenied,	// Caller does not have enough permissions to execute the request
		ResourceExhausted,	// Request is valid but cannot be fulfilled due to exhaustion of some underlying resource on the callee's side, e.g., not enough disk space.
		UnknownError		// Error is not classified
	};
}
