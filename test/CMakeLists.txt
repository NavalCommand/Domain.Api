find_package(GTest CONFIG REQUIRED)
include(GoogleTest)
find_package(Python3 REQUIRED COMPONENTS Interpreter)

set(domainTestSources)
file(GLOB_RECURSE domainTestSources CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/NavalCommand/*.cpp")

add_executable(NavalCommand.Domain.Api.Test ${domainTestSources})
target_link_libraries(NavalCommand.Domain.Api.Test PRIVATE
        NavalCommand.Physics.Api
        NavalCommand.Uncertainty.Api
        NavalCommand.Error.Api
        NavalCommand.Classification.Api
        NavalCommand.Resources.Api
        NavalCommand.Equipment.Api
        NavalCommand.Factions.Api
        NavalCommand.Units.Api
        NavalCommand.Observations.Api
        NavalCommand.Operations.Api
        NavalCommand.Orders.Api
        NavalCommand.Environment.Api
        NavalCommand.Simulation.Api
        GTest::gtest_main
        GTest::gmock)
target_include_directories(NavalCommand.Domain.Api.Test PRIVATE "${PROJECT_SOURCE_DIR}/mock")
NavalCommandConfigureDomainTarget(NavalCommand.Domain.Api.Test)
gtest_discover_tests(NavalCommand.Domain.Api.Test DISCOVERY_MODE PRE_TEST)
