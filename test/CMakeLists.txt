find_package(Python3 REQUIRED COMPONENTS Interpreter)
include("${CMAKE_CURRENT_SOURCE_DIR}/ExportDomainGraph.cmake")

add_test(NAME domain-architecture
    COMMAND "${Python3_EXECUTABLE}" -B "${CMAKE_CURRENT_SOURCE_DIR}/CheckArchitecture.py"
        --root "${PROJECT_SOURCE_DIR}" --targets "${CMAKE_CURRENT_BINARY_DIR}/domain-targets.txt")
add_test(NAME domain-architecture-negative
    COMMAND "${Python3_EXECUTABLE}" -B "${CMAKE_CURRENT_SOURCE_DIR}/ArchitectureTests.py" --cmake "${CMAKE_COMMAND}")

set(domainSmokeTests
    Physics:PhysicsHeaderSmoke.cpp
    Uncertainty:UncertaintyHeaderSmoke.cpp
    Error:ErrorHeaderSmoke.cpp
    Resources:ResourcesHeaderSmoke.cpp
    Equipment:EquipmentHeaderSmoke.cpp
    Factions:FactionsHeaderSmoke.cpp
    Units:UnitsHeaderSmoke.cpp
    Observations:ObservationsHeaderSmoke.cpp
    Orders:OrdersHeaderSmoke.cpp
    Environment:EnvironmentHeaderSmoke.cpp
    Simulation:SimulationHeaderSmoke.cpp)

foreach(smoke IN LISTS domainSmokeTests)
    string(REPLACE ":" ";" smokeFields "${smoke}")
    list(GET smokeFields 0 domain)
    list(GET smokeFields 1 source)
    string(TOLOWER "${domain}" lowerDomain)
    add_executable("${lowerDomain}-header-smoke" "${source}")
    target_link_libraries("${lowerDomain}-header-smoke" PRIVATE "${domain}.Api")
    NavalCommandConfigureDomainTarget("${lowerDomain}-header-smoke")
    add_test(NAME "${lowerDomain}-headers" COMMAND "${lowerDomain}-header-smoke")
endforeach()

# Each exported header is consumed directly and linked through its owning domain target.
file(GLOB_RECURSE domainHeaders CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/public/*.h")
foreach(header IN LISTS domainHeaders)
    file(RELATIVE_PATH relativeHeader "${PROJECT_SOURCE_DIR}/public" "${header}")
    if(NOT relativeHeader MATCHES "^NavalCommand/([A-Za-z]+)/Api/[^/]+\\.h$")
        message(FATAL_ERROR "Invalid exported header ownership path: ${relativeHeader}")
    endif()
    set(ownerTarget "${CMAKE_MATCH_1}.Api")
    if(NOT TARGET "${ownerTarget}")
        message(FATAL_ERROR "No populated domain target owns ${relativeHeader}: ${ownerTarget}")
    endif()
    string(MAKE_C_IDENTIFIER "${relativeHeader}" headerTarget)
    set(source "${CMAKE_CURRENT_BINARY_DIR}/${headerTarget}.cpp")
    file(WRITE "${source}" "#include <${relativeHeader}>\nint main() { return 0; }\n")
    add_executable("header-${headerTarget}" "${source}")
    target_link_libraries("header-${headerTarget}" PRIVATE "${ownerTarget}")
    NavalCommandConfigureDomainTarget("header-${headerTarget}")
    add_test(NAME "standalone-${headerTarget}" COMMAND "header-${headerTarget}")
endforeach()
