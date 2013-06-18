# Function for adding a precompiled header to a project
# Uses the ${precompiled_header} for all ${source_files} by creating it from
# ${precompiled_source}.
#
# ${source_files} will have the /MP flag for multicore compilation

function (add_precompiled_header precompiled_header precompiled_source source_files)
    if (WIN32)
        _add_msvc_precompiled_header(
            ${precompiled_header}
            ${precompiled_source}
            "${source_files}")
    endif()
endfunction()


# Microsot Visual Studio support for precompiled header
# Adds /MP flag for multicore support to all source files except the ${precompiled_source}

function (_add_msvc_precompiled_header precompiled_header precompiled_source source_files)
    get_filename_component(PrecompiledBasename ${precompiled_header} NAME_WE)
    set(PrecompiledBinary "$(IntDir)/${PrecompiledBasename}.pch")

    list(REMOVE_ITEM source_files ${CMAKE_CURRENT_SOURCE_DIR}/${precompiled_source})

    set_source_files_properties(
        ${precompiled_source}
        PROPERTIES COMPILE_FLAGS
            "/Yc\"${precompiled_header}\" /Fp\"${PrecompiledBinary}\""
        OBJECT_OUTPUTS "${PrecompiledBinary}")

    set_source_files_properties(
        ${source_files}
        PROPERTIES COMPILE_FLAGS
            "/Yu\"${precompiled_header}\" /FI\"${PrecompiledBinary}\" /Fp\"${PrecompiledBinary}\" /MP"
        OBJECT_DEPENDS "${PrecompiledBinary}")
endfunction()
