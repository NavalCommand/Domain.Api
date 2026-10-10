add_library(Orders.Api INTERFACE)
target_include_directories(Orders.Api INTERFACE "${PROJECT_SOURCE_DIR}/public")
NavalCommandConfigureTarget(Orders.Api)

add_library(World.Api INTERFACE)
target_include_directories(World.Api INTERFACE "${PROJECT_SOURCE_DIR}/public")
target_link_libraries(World.Api INTERFACE Orders.Api)
NavalCommandConfigureTarget(World.Api)
