cmake_minimum_required(VERSION 2.8.12.1)

# Only generate Debug and Release configuration types.
set(CMAKE_CONFIGURATION_TYPES Debug Release)
set(CMAKE_CXX_STANDARD 17)

#project name
project(we_media)

# Use folders in the resulting project files.
set_property(GLOBAL PROPERTY OS_FOLDERS ON)

# Specify the CEF distribution version.
set(CEF_VERSION "3.3497.1827.ga4f7e36")

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

# Example executable targets.
add_subdirectory(src/cefclient)
add_subdirectory(src/cefsimple)
