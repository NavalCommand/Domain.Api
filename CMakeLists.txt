cmake_minimum_required(VERSION 4.2)
cmake_policy(SET CMP0168 NEW)
project(Domain.Api VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
    ncbuild
    GIT_REPOSITORY https://github.com/NavalCommand/Build.CMake.git
    GIT_TAG main)
FetchContent_MakeAvailable(ncbuild)
include("${ncbuild_SOURCE_DIR}/NavalCommand.Build.CMake.cmake")

function(NavalCommandConfigureDomainTarget target)
    NavalCommandConfigureTarget("${target}")
    set_target_properties("${target}" PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO)
    get_target_property(targetType "${target}" TYPE)
    if(targetType STREQUAL "INTERFACE_LIBRARY")
        set_property(TARGET "${target}" PROPERTY INTERFACE_COMPILE_FEATURES cxx_std_23)
    endif()
endfunction()

NavalCommandConfigureModule()
