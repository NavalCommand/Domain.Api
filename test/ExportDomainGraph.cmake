# Read final direct properties after configuration. TARGET_PROPERTY generator expressions
# expand transitive links under CMP0189 and would falsely turn Orders -> Units -> Catalog
# into a direct Orders -> Catalog edge. Raw expressions are intentionally rejected.
function(NavalCommandExportDomainGraph)
    get_property(graphPath GLOBAL PROPERTY NAVALCOMMAND_DOMAIN_GRAPH_PATH)
    set(domainTargetNames Physics.Api Uncertainty.Api Catalog.Api Units.Api Orders.Api World.Api)
    if(TARGET Environment.Api)
        list(APPEND domainTargetNames Environment.Api)
    endif()
    set(domainGraphContent "")
    foreach(domainTarget IN LISTS domainTargetNames)
        get_target_property(directLinks "${domainTarget}" INTERFACE_LINK_LIBRARIES)
        if(NOT directLinks)
            set(directLinks "")
        endif()
        string(APPEND domainGraphContent "${domainTarget}|${directLinks}\n")
    endforeach()
    file(WRITE "${graphPath}" "${domainGraphContent}")
endfunction()

set_property(GLOBAL PROPERTY NAVALCOMMAND_DOMAIN_GRAPH_PATH "${CMAKE_CURRENT_BINARY_DIR}/domain-targets.txt")
cmake_language(DEFER DIRECTORY "${CMAKE_SOURCE_DIR}" CALL NavalCommandExportDomainGraph)
