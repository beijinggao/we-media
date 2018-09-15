#
# Source files.
#

set(WE_MEDIA_MAC_SRCS
        mac/AppDelegate.h
        mac/AppDelegate.mm
        mac/WMWindow.h
        Mac/WMWindow.mm
        )

source_group(core\\\\mac FILES ${WE_MEDIA_MAC_SRCS})


#cefclient Mac OS X sources
set(WE_MEDIA_MACOSX_SRCS
        main_mac.mm
        )

source_group(core FILES ${WE_MEDIA_MACOSX_SRCS})

# Target executable names.
set(WEMEDIA_TARGET "we-media")

# Logical target used to link the libcef library.
ADD_LOGICAL_TARGET("libcef_lib" "${CEF_LIB_DEBUG}" "${CEF_LIB_RELEASE}")

# Determine the target output directory.
SET_CEF_TARGET_OUT_DIR()

#
# Mac OS X configuration.
#

if(OS_MACOSX)
    # All sources required by the "cefclient" target. Generates an app bundle that
    # is used only for the browser process.
    set(WEMEDIA_SRCS
            ${WE_MEDIA_MAC_SRCS}
            ${WE_MEDIA_MACOSX_SRCS}
            )

    # Output paths for the app bundles.
    set(WEMEDIA_APP "${CEF_TARGET_OUT_DIR}/${WEMEDIA_TARGET}.app")

    # Variable referenced from Info.plist files.
    set(PRODUCT_NAME "${WEMEDIA_TARGET}")

    # Main executable target.
    add_executable(${WEMEDIA_TARGET} MACOSX_BUNDLE ${WEMEDIA_SRCS})
    SET_EXECUTABLE_TARGET_PROPERTIES(${WEMEDIA_TARGET})
    add_dependencies(${WEMEDIA_TARGET} libcef_dll_wrapper)
    target_link_libraries(${WEMEDIA_TARGET} libcef_lib libcef_dll_wrapper ${CEF_STANDARD_LIBS} "-framework OpenGL")
    #set_target_properties(${WEMEDIA_TARGET} PROPERTIES
     #       MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/resources/mac/Info.plist
     #       )

    # Copy files into the main app bundle.
    add_custom_command(
            TARGET ${WEMEDIA_TARGET}
            POST_BUILD
            # Copy the CEF framework into the Frameworks directory.
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CEF_BINARY_DIR}/Chromium Embedded Framework.framework"
            "${WEMEDIA_APP}/Contents/Frameworks/Chromium Embedded Framework.framework"
            VERBATIM
    )

    # Fix the framework rpath in the main executable.
    FIX_MACOSX_MAIN_FRAMEWORK_RPATH(${WEMEDIA_TARGET})

    # Manually process and copy over resource files.
    # The Xcode generator can support this via the set_target_properties RESOURCE
    # directive but that doesn't properly handle nested resource directories.
    # Remove these prefixes from input file paths.
    #set(PREFIXES
    #        "resources/mac/"
    #        "resources/"
    #        "../shared/resources/"
    #        )
    #COPY_MACOSX_RESOURCES("${CEFCLIENT_RESOURCES_SRCS}" "${PREFIXES}" "${CEF_TARGET}" "${CMAKE_CURRENT_SOURCE_DIR}" "${CEF_APP}")
endif()


#
# Windows configuration.
#

if(OS_WINDOWS)
    # All sources required by the "cefclient" target. Generates an executable that
    # is used for all processes.
    set(CEFCLIENT_SRCS
            ${CEFCLIENT_BROWSER_SRCS}
            ${CEFCLIENT_COMMON_SRCS}
            ${CEFCLIENT_RENDERER_SRCS}
            ${CEFCLIENT_RESOURCES_SRCS}
            ${CEFCLIENT_WINDOWS_SRCS}
            )

    # Executable target.
    add_executable(${CEF_TARGET} WIN32 ${CEFCLIENT_SRCS})
    SET_EXECUTABLE_TARGET_PROPERTIES(${CEF_TARGET})
    add_dependencies(${CEF_TARGET} libcef_dll_wrapper)
    target_link_libraries(${CEF_TARGET} libcef_lib libcef_dll_wrapper ${CEF_STANDARD_LIBS} glu32.lib imm32.lib opengl32.lib)

    if(USE_ATL)
        # Required by VS2013 to link accessibility API functions.
        target_link_libraries(${CEF_TARGET} oleacc.lib)
    endif()

    if(USE_SANDBOX)
        # Logical target used to link the cef_sandbox library.
        ADD_LOGICAL_TARGET("cef_sandbox_lib" "${CEF_SANDBOX_LIB_DEBUG}" "${CEF_SANDBOX_LIB_RELEASE}")
        target_link_libraries(${CEF_TARGET} cef_sandbox_lib ${CEF_SANDBOX_STANDARD_LIBS})
    endif()

    # Add the custom manifest files to the executable.
    ADD_WINDOWS_MANIFEST("${CMAKE_CURRENT_SOURCE_DIR}/resources/win" "${CEF_TARGET}" "exe")

    # Copy CEF binary and resource files to the target output directory.
    COPY_FILES("${CEF_TARGET}" "${CEF_BINARY_FILES}" "${CEF_BINARY_DIR}" "${CEF_TARGET_OUT_DIR}")
    COPY_FILES("${CEF_TARGET}" "${CEF_RESOURCE_FILES}" "${CEF_RESOURCE_DIR}" "${CEF_TARGET_OUT_DIR}")
endif()