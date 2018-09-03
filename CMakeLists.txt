cmake_minimum_required(VERSION 2.8.12.1)

# Only generate Debug and Release configuration types.
set(CMAKE_CONFIGURATION_TYPES Debug Release)
set(CMAKE_CXX_STANDARD 17)

#project name
project(we_media)

# Use folders in the resulting project files.
set_property(GLOBAL PROPERTY OS_FOLDERS ON)

# Specify the CEF distribution version.
set(CEF_VERSION "3.3396.1777.g636f29b")

# Determine the platform.
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
    set(CEF_PLATFORM "macosx64")
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    if(CMAKE_SIZEOF_VOID_P MATCHES 8)
        set(CEF_PLATFORM "linux64")
    else()
        set(CEF_PLATFORM "linux32")
    endif()
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
    if(CMAKE_SIZEOF_VOID_P MATCHES 8)
        set(CEF_PLATFORM "windows64")
    else()
        set(CEF_PLATFORM "windows32")
    endif()
endif()

# Add this project's cmake/ directory to the module path.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Download and extract the CEF binary distribution (executes DownloadCEF.cmake).
include(DownloadCEF)
DownloadCEF("${CEF_PLATFORM}" "${CEF_VERSION}" "${CMAKE_SOURCE_DIR}/third_party/cef")

# Add the CEF binary distribution's cmake/ directory to the module path.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CEF_ROOT}/cmake")

# Load the CEF configuration (executes FindCEF.cmake).
find_package(CEF REQUIRED)


#
# Python configuration.
#

# Support specification of the Python executable path via the command-line.
if(DEFINED ENV{PYTHON_EXECUTABLE})
    file(TO_CMAKE_PATH "$ENV{PYTHON_EXECUTABLE}" PYTHON_EXECUTABLE)
endif()

if(NOT PYTHON_EXECUTABLE)
    unset(PYTHON_EXECUTABLE)

    # Find the python interpreter.
    find_package(PythonInterp)

    if(NOT ${PYTHONINTERP_FOUND})
        message(FATAL_ERROR "A Python installation is required. Set the "
                "PYTHON_EXECUTABLE environment variable to explicitly "
                "specify the Python executable path.")
    endif()
endif()


#
# Clang-format configuration.
#

if(OS_WINDOWS)
    set(GS_PLATFORM "win32")
    set(GS_HASHPATH "win/clang-format.exe.sha1")
elseif(OS_MACOSX)
    set(GS_PLATFORM "darwin")
    set(GS_HASHPATH "mac/clang-format.sha1")
elseif(OS_LINUX)
    set(GS_PLATFORM "linux*")
    set(GS_HASHPATH "linux64/clang-format.sha1")
endif()

message(STATUS "Downloading clang-format from Google Storage...")
execute_process(
        COMMAND "${PYTHON_EXECUTABLE}"
        "tools/buildtools/download_from_google_storage.py"
        "--no_resume"
        "--platform=${GS_PLATFORM}"
        "--no_auth"
        "--bucket" "chromium-clang-format"
        "-s" "tools/buildtools/${GS_HASHPATH}"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        RESULT_VARIABLE EXECUTE_RV
)
if(NOT EXECUTE_RV STREQUAL "0")
    message(FATAL_ERROR "Execution failed with unexpected result: ${EXECUTE_RV}")
endif()


#
# Target configuration.
#

# Include the libcef_dll_wrapper target (executes libcef_dll/CMakeLists.txt).
add_subdirectory(${CEF_LIBCEF_DLL_WRAPPER_PATH} libcef_dll_wrapper)

# Include CEF's test application targets (executes <target>/CMakeLists.txt).
#add_subdirectory(${CEF_ROOT}/tests/cefclient)

# Allow includes relative to the current source directory.
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CEF_ROOT}
)

# Display configuration settings.
PRINT_CEF_CONFIG()

if(OS_MACOSX)
    # Shared macOS resources (menus, icons, etc).
    set(SHARED_RESOURCES_SRCS
            ../shared/resources/mac/English.lproj/InfoPlist.strings
            ../shared/resources/mac/English.lproj/MainMenu.xib
            ../shared/resources/mac/Info.plist
            ../shared/resources/mac/shared.icns
            )

    # Info.plist files used for main and helper app bundles.
    set(SHARED_INFO_PLIST ../shared/resources/mac/Info.plist)
    set(SHARED_HELPER_INFO_PLIST ../shared/resources/mac/helper-Info.plist)
elseif(OS_WINDOWS)
    # Shared Windows resources (version information, icons).
    set(SHARED_RESOURCES_SRCS
            ../shared/resources/win/big.ico
            ../shared/resources/win/resource.h
            ../shared/resources/win/shared.rc
            ../shared/resources/win/small.ico
            )

    # Manifest files used for executables.
    set(SHARED_EXE_MANIFEST ../shared/resources/win/shared.exe.manifest)
    set(SHARED_COMPATIBILITY_MANIFEST ../shared/resources/win/compatibility.manifest)
endif()


#
# Shared configuration.
#

# Support nice project/target organization in Visual Studio and Xcode.
if(OS_MACOSX OR OS_WINDOWS)
    # Enable the creation of project folders.
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    # Group target contents by directory.
    macro(SET_EXAMPLE_SOURCE_GROUPS srcs)
        foreach(FILE ${srcs})
            # Get the absolute directory path.
            get_filename_component(ABS_FILE "${FILE}" ABSOLUTE)
            get_filename_component(PARENT_DIR "${ABS_FILE}" DIRECTORY)

            # Remove the common directory prefix. What remains in the group.
            string(REPLACE "${CMAKE_SOURCE_DIR}/examples/" "" GROUP "${PARENT_DIR}")

            # Convert to Windows slashes.
            string(REPLACE "/" "\\" GROUP "${GROUP}")

            source_group("${GROUP}" FILES "${FILE}")
        endforeach()
    endmacro()
endif()

# Set the configuration-specific binary output directory.
if(GEN_NINJA OR GEN_MAKEFILES)
    # Force Ninja and Make to create a subdirectory named after the configuration.
    set(WEMEDIA_TARGET_OUT_DIR "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}")
else()
    set(WEMEDIA_TARGET_OUT_DIR "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
endif()

# Set properties common to all example targets.
macro(SET_EXAMPLE_PROPERTIES target)
    # Output all binaries to the configuration-specific build directory.
    set_target_properties(${target} PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${WEMEDIA_TARGET_OUT_DIR}"
            RUNTIME_OUTPUT_DIRECTORY "${WEMEDIA_TARGET_OUT_DIR}"
            LIBRARY_OUTPUT_DIRECTORY "${WEMEDIA_TARGET_OUT_DIR}")

    if(OS_MACOSX OR OS_WINDOWS)
        # Place the target in the "examples" folder in Visual Studio and Xcode.
        set_property(TARGET ${target} PROPERTY FOLDER "examples")
    endif()
endmacro()

# Set properties on an example library target.
macro(SET_EXAMPLE_LIBRARY_TARGET_PROPERTIES target)
    SET_LIBRARY_TARGET_PROPERTIES(${target})
    SET_EXAMPLE_PROPERTIES(${target})
endmacro()

# Set properties on an example executable target.
macro(SET_EXAMPLE_EXECUTABLE_TARGET_PROPERTIES target)
    SET_EXECUTABLE_TARGET_PROPERTIES(${target})
    SET_EXAMPLE_PROPERTIES(${target})

    if(OS_LINUX)
        # Set rpath so that libraries can be placed next to the executable.
        set_target_properties(${target} PROPERTIES INSTALL_RPATH "$ORIGIN")
        set_target_properties(${target} PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)
    elseif(OS_WINDOWS)
        # Add the custom Windows manifest files to the executable.
        add_custom_command(
                TARGET ${target}
                POST_BUILD
                COMMAND "mt.exe" -nologo
                -manifest \"${CMAKE_CURRENT_SOURCE_DIR}/${SHARED_EXE_MANIFEST}\"
                \"${CMAKE_CURRENT_SOURCE_DIR}/${SHARED_COMPATIBILITY_MANIFEST}\"
                -outputresource:"${EXAMPLE_TARGET_OUT_DIR}/${target}.exe"\;\#1
                COMMENT "Adding manifest..."
        )
    endif()
endmacro()

#
# Target configuration.
#
set(WEMEDIA_TARGET "we-media")

# Static library shared by all example executable targets.
#add_subdirectory(src/shared)

# Example executable targets.
#add_subdirectory(src/minimal)

# Logical target used to link the libcef library.
ADD_LOGICAL_TARGET("libcef_lib" "${CEF_LIB_DEBUG}" "${CEF_LIB_RELEASE}")

set(APP_SRCS src)

file(GLOB_RECURSE
        SOURCE_FILES
        ${APP_SRCS}/*.cpp
        ${APP_SRCS}/*.h
        #${APP_SRCS}/main.cpp
        #${APP_SRCS}/core/request_url.h
        #${APP_SRCS}/core/request_url.cpp

)

#if(OS_MACOSX)
    # Main static library target.
#    link_directories(${CEF_ROOT}/Release)

#   add_executable(we_media ${SOURCE_FILES})
#    add_dependencies(we_media libcef_dll_wrapper)
#    target_link_libraries(we_media libcef_lib libcef_dll_wrapper ${CEF_STANDARD_LIBS})
#    SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
#endif()

#
# Mac OS X configuration.
#

if(OS_MACOSX)
    # Create source groups for Xcode.
    SET_EXAMPLE_SOURCE_GROUPS("${SOURCE_FILES}")

    # Output paths for the app bundles.
    set(WEMEDIA_APP "${WEMEDIA_TARGET_OUT_DIR}/${WEMEDIA_TARGET}.app")

    # Variable referenced from Info.plist files.
    set(PRODUCT_NAME "${WEMEDIA_TARGET}")

    # Main executable target.
    add_executable(${WEMEDIA_TARGET} MACOSX_BUNDLE ${SOURCE_FILES})
    SET_EXAMPLE_EXECUTABLE_TARGET_PROPERTIES(${WEMEDIA_TARGET})
    #add_dependencies(${WEMEDIA_TARGET})
    #target_link_libraries(${WEMEDIA_TARGET})

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

    if(NOT ${CMAKE_GENERATOR} STREQUAL "Xcode")
        # Manually process and copy over resource files.
        # The Xcode generator handles this via the set_target_properties RESOURCE directive.
        # Remove these prefixes from input file paths.
        set(PREFIXES
                "../shared/resources/mac/"
                )
        COPY_MACOSX_RESOURCES("${SOURCE_FILES}" "${PREFIXES}" "${WEMEDIA_TARGET}" "${CMAKE_CURRENT_SOURCE_DIR}" "${WEMEDIA_APP}")
    endif()
endif()


#
# Windows configuration.
#

if(OS_WINDOWS)
    # Add resources to the sources variable for convenience.
    set(EXAMPLE_SRCS
            ${EXAMPLE_SRCS}
            ${EXAMPLE_RESOURCES_SRCS}
            )

    # Create source groups for Visual Studio.
    SET_EXAMPLE_SOURCE_GROUPS("${EXAMPLE_SRCS}")

    # Executable target.
    add_executable(${EXAMPLE_TARGET} WIN32 ${EXAMPLE_SRCS})
    SET_EXAMPLE_EXECUTABLE_TARGET_PROPERTIES(${EXAMPLE_TARGET})
    add_dependencies(${EXAMPLE_TARGET} shared)
    target_link_libraries(${EXAMPLE_TARGET} shared)
endif()