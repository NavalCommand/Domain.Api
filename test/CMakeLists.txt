add_executable(orders-header-smoke OrdersHeaderSmoke.cpp)
target_link_libraries(orders-header-smoke PRIVATE Orders.Api)
NavalCommandConfigureTarget(orders-header-smoke)
add_test(NAME orders-headers COMMAND orders-header-smoke)

add_executable(world-header-smoke WorldHeaderSmoke.cpp)
target_link_libraries(world-header-smoke PRIVATE World.Api)
NavalCommandConfigureTarget(world-header-smoke)
add_test(NAME world-headers COMMAND world-header-smoke)
