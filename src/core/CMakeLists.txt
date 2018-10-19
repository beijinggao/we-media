#
# Source files.
#

set(WE_MEDIA_MAC_SRCS
        mac/AppDelegate.h
        mac/AppDelegate.mm
        mac/Application.h
        mac/Application.mm
        mac/SimpleApp.h
        mac/SimpleApp.mm
        mac/SimpleHandler.h
        mac/SimpleHandler.cpp
        mac/SimpleHandlerMac.mm
        mac/CustomScheme.h
        mac/CustomScheme.cpp
        mac/test_runner.h
        mac/test_runner.cc
        mac/resource_util.h
        mac/resource_util_posix.cc
        mac/resource_util_mac.mm
        )

source_group(core\\\\mac FILES ${WE_MEDIA_MAC_SRCS})

# cefsimple helper sources.
set(WE_MEDIA_HELPER_SRCS_MACOSX
        mac/ProcessHelperMac.cpp
        )
APPEND_PLATFORM_SOURCES(WE_MEDIA_HELPER_SRCS)
source_group(core\\\\mac FILES ${WE_MEDIA_HELPER_SRCS})

#cefclient Mac OS X sources
set(WE_MEDIA_MACOSX_SRCS
        main_mac.mm
        )

source_group(core FILES ${WE_MEDIA_MACOSX_SRCS})

# cefsimple resources.
set(WE_MEDIA_RESOURCES_MAC_SRCS_MACOSX
        mac/res/Info.plist
        mac/res/cefsimple.icns
        )
APPEND_PLATFORM_SOURCES(WE_MEDIA_RESOURCES_MAC_SRCS)
source_group(core\\\\mac\\\\res FILES ${WE_MEDIA_RESOURCES_MAC_SRCS})

set(WE_MEDIA_RESOURCES_MAC_ENGLISH_LPROJ_SRCS_MACOSX
        mac/res/English.lproj/InfoPlist.strings
        mac/res/English.lproj/MainMenu.xib
        )
APPEND_PLATFORM_SOURCES(WE_MEDIA_RESOURCES_MAC_ENGLISH_LPROJ_SRCS)
source_group(core\\\\mac\\\\res\\\\English.lproj FILES ${WE_MEDIA_RESOURCES_MAC_ENGLISH_LPROJ_SRCS})

set(WE_MEDIA_RESOURCES_HTML_MAC_SRCS_MACOSX
        mac/res/html/login.htm
        mac/res/html/css/4HCPitP8ZT9.css
        mac/res/html/css/ZvcBLy34iDb.css
        mac/res/html/js/fbevents.js
        mac/res/html/js/0VHSCIdeo-7.js
        mac/res/html/js/4Lrn03CojQY.js
        mac/res/html/js/106mWwOdaQc.js
        mac/res/html/js/agaaxOoNaht.js
        mac/res/html/js/aKKaDLg6cM7.js
        mac/res/html/js/BGl7oDL8Em2.js
        mac/res/html/js/c2Ep_m78lwa.js
        mac/res/html/js/CD02CfEgs_A.js
        mac/res/html/js/Ilm1TuLsvhw.js
        mac/res/html/js/k0kqXaiDWnJ.js
        mac/res/html/js/sOiK3R2YIAy.js
        mac/res/html/js/W0sXB4uYYyH.js
        mac/res/html/js/xALXySgI5G9.js
        mac/res/html/js/yEQ4aOhmjyj.js
        mac/res/html/js/zHR-Nmgf70-.js
        mac/res/html/imgs/O6n_HQxozp9.ico
        mac/res/html/imgs/logo.png
        )
APPEND_PLATFORM_SOURCES(WE_MEDIA_RESOURCES_HTML_MAC_SRCS)
source_group(core\\\\mac\\\\res FILES ${WE_MEDIA_RESOURCES_HTML_MAC_SRCS})


set(WE_MEDIA_RESOURCES_SRCS
        ${WE_MEDIA_RESOURCES_MAC_SRCS}
        ${WE_MEDIA_RESOURCES_MAC_ENGLISH_LPROJ_SRCS}
        ${WE_MEDIA_RESOURCES_HTML_MAC_SRCS}
        )

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

    set(WEMEDIA_HELPER_TARGET "we-media_Helper")
    set(WEMEDIA_HELPER_OUTPUT_NAME "we-media Helper")

    # Output paths for the app bundles.
    set(WEMEDIA_APP "${CEF_TARGET_OUT_DIR}/${WEMEDIA_TARGET}.app")
    set(WEMEDIA_HELPER_APP "${CEF_TARGET_OUT_DIR}/${WEMEDIA_HELPER_OUTPUT_NAME}.app")

    # Variable referenced from Info.plist files.
    set(PRODUCT_NAME "${WEMEDIA_TARGET}")

    # Helper executable target.
    add_executable(${WEMEDIA_HELPER_TARGET} MACOSX_BUNDLE ${WE_MEDIA_HELPER_SRCS})
    SET_EXECUTABLE_TARGET_PROPERTIES(${WEMEDIA_HELPER_TARGET})
    add_dependencies(${WEMEDIA_HELPER_TARGET} libcef_dll_wrapper)
    target_link_libraries(${WEMEDIA_HELPER_TARGET} libcef_lib libcef_dll_wrapper ${CEF_STANDARD_LIBS})
    set_target_properties(${WEMEDIA_HELPER_TARGET} PROPERTIES
            MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/mac/res/helper-Info.plist
            OUTPUT_NAME ${WEMEDIA_HELPER_OUTPUT_NAME}
            )

    # Fix the framework rpath in the helper executable.
    FIX_MACOSX_HELPER_FRAMEWORK_RPATH(${WEMEDIA_HELPER_TARGET})

    # Main executable target.
    add_executable(${WEMEDIA_TARGET} MACOSX_BUNDLE ${WE_MEDIA_RESOURCES_SRCS} ${WEMEDIA_SRCS})
    SET_EXECUTABLE_TARGET_PROPERTIES(${WEMEDIA_TARGET})
    add_dependencies(${WEMEDIA_TARGET} libcef_dll_wrapper "${WEMEDIA_HELPER_TARGET}")
    target_link_libraries(${WEMEDIA_TARGET} libcef_lib libcef_dll_wrapper ${CEF_STANDARD_LIBS})
    set_target_properties(${WEMEDIA_TARGET} PROPERTIES
            MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/mac/res/Info.plist
            )

    # Copy files into the main app bundle.
    add_custom_command(
            TARGET ${WEMEDIA_TARGET}
            POST_BUILD
            # Copy the helper app bundle into the Frameworks directory.
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${WEMEDIA_HELPER_APP}"
            "${WEMEDIA_APP}/Contents/Frameworks/${WEMEDIA_HELPER_OUTPUT_NAME}.app"
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
    set(PREFIXES "mac/res/")
    COPY_MACOSX_RESOURCES("${WE_MEDIA_RESOURCES_SRCS}" "${PREFIXES}" "${WEMEDIA_TARGET}" "${CMAKE_CURRENT_SOURCE_DIR}" "${WEMEDIA_APP}")
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