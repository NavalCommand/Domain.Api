add_library(Physics.Api INTERFACE)
target_include_directories(Physics.Api INTERFACE "${PROJECT_SOURCE_DIR}/public")
NavalCommandConfigureTarget(Physics.Api)

add_library(Uncertainty.Api INTERFACE)
target_include_directories(Uncertainty.Api INTERFACE "${PROJECT_SOURCE_DIR}/public")
NavalCommandConfigureTarget(Uncertainty.Api)

add_library(Catalog.Api INTERFACE)
target_include_directories(Catalog.Api INTERFACE "${PROJECT_SOURCE_DIR}/public")
target_link_libraries(Catalog.Api INTERFACE Physics.Api)
NavalCommandConfigureTarget(Catalog.Api)

add_library(Units.Api INTERFACE)
target_include_directories(Units.Api INTERFACE "${PROJECT_SOURCE_DIR}/public")
target_link_libraries(Units.Api INTERFACE Catalog.Api Physics.Api Uncertainty.Api)
NavalCommandConfigureTarget(Units.Api)

add_library(Orders.Api INTERFACE)
target_include_directories(Orders.Api INTERFACE "${PROJECT_SOURCE_DIR}/public")
target_link_libraries(Orders.Api INTERFACE Units.Api Physics.Api Uncertainty.Api)
NavalCommandConfigureTarget(Orders.Api)

# Environment.Api remains reserved until a provider exposes supported environment facts.
add_library(World.Api INTERFACE)
target_include_directories(World.Api INTERFACE "${PROJECT_SOURCE_DIR}/public")
target_link_libraries(World.Api INTERFACE Units.Api Physics.Api Uncertainty.Api)
NavalCommandConfigureTarget(World.Api)
