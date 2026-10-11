#include <NavalCommand/World/Api/View.h>
#include <stdexcept>
#include <type_traits>

namespace World = NavalCommand::World::Api;
namespace Units = NavalCommand::Units::Api;
namespace Physics = NavalCommand::Physics::Api;
namespace Uncertainty = NavalCommand::Uncertainty::Api;

static void Require(bool condition)
{
	if (!condition)
	{
		throw std::runtime_error("World relationship assertion failed");
	}
}

int main()
{
	static_assert(std::is_same_v<decltype(Units::UnitInstance::Identity), Units::UnitId>);
	static_assert(std::is_same_v<decltype(World::UnitMembership::Unit), Units::UnitId>);
	World::View snapshot;
	snapshot.SessionId = "session";
	snapshot.ObserverId = "observer";
	snapshot.Version = 7;
	snapshot.CapturedAt = {45};
	snapshot.Instances.resize(3);
	auto& own = snapshot.Instances[0];
	own.Identity = {"session-observation-1"};
	own.Observation.MeasuredAt = Uncertainty::Knowledge<Physics::Seconds>::Known({40});
	auto& contact = snapshot.Instances[1];
	contact.Identity = {"session-observation-2"};
	contact.Kinematics.Position = Uncertainty::Knowledge<Units::PositionObservation>::Estimated({{{1}, {2}, std::nullopt}, std::nullopt}, "faction-visible contact evidence");
	auto& airfield = snapshot.Instances[2];
	airfield.Identity = {"session-observation-3"};
	airfield.AirOperations.emplace();
	airfield.AirOperations->PendingOperations = Uncertainty::Knowledge<std::uint32_t>::Known(0);
	Require(!contact.Observation.MeasuredAt.HasValue());
	Require(snapshot.CapturedAt.Value - own.Observation.MeasuredAt.Value().Value == 5);
	Require(airfield.Identity == snapshot.Instances[2].Identity && airfield.AirOperations.has_value());

	using Memberships = Uncertainty::ObservedCollection<World::UnitMembership>;
	Require(snapshot.Memberships.GetCoverage() == Memberships::Coverage::Unknown);
	snapshot.Memberships = {
		Memberships::Coverage::Partial,
		{{own.Identity, Uncertainty::Knowledge<std::string>::Known("observer-visible-faction"), Uncertainty::Knowledge<std::string>::Known("session-taskforce-1")},
		 {contact.Identity, {}, {}}}};
	Require(snapshot.Memberships.Items()[0].Unit == own.Identity);
	Require(snapshot.Memberships.Items()[0].TaskForce.Value() == "session-taskforce-1");
	Require(!snapshot.Memberships.Items()[1].Faction.HasValue());
	Require(!snapshot.Memberships.Items()[1].TaskForce.HasValue());
	Require(snapshot.Memberships.GetCoverage() == Memberships::Coverage::Partial);
	snapshot.Memberships = {Memberships::Coverage::Complete, {}};
	Require(snapshot.Memberships.Items().empty());
	return 0;
}
