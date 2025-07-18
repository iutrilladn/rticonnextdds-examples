#
# (c) 2024 Copyright, Real-Time Innovations, Inc.  All rights reserved.
#
#  RTI grants Licensee a license to use, modify, compile, and create derivative
#  works of the Software.  Licensee has the right to distribute object form
#  only for use with RTI products.  The Software is provided "as is", with no
#  warranty of any type, including any warranty for fitness for any purpose.
#  RTI is under no obligation to maintain or support the Software.  RTI shall
#  not be liable for any incidental or consequential damages arising out of the
#  use or inability to use the software.
#
cmake_minimum_required(VERSION 3.11)
project(SocketAdapterCpp)

# Find RTI Connext dependencies
list(APPEND CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../resources/cmake/Modules"
)
include(ConnextDdsConfigureCmakeUtils)
connextdds_configure_cmake_utils()

find_package(
    RTIConnextDDS "7.3.0"
    REQUIRED
    COMPONENTS
        core
        routing_service
)

# It may not be necessary to include the hpp files
add_library(${PROJECT_NAME}
    "${CMAKE_CURRENT_SOURCE_DIR}/src/SocketAdapter.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/SocketAdapter.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/SocketConnection.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/SocketConnection.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/SocketInputDiscoveryStreamReader.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/SocketInputDiscoveryStreamReader.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/SocketStreamReader.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/SocketStreamReader.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/SocketStreamWriter.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/SocketStreamWriter.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/UdpSocket.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/UdpSocket.hpp"
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(${PROJECT_NAME}
    RTIConnextDDS::routing_service_infrastructure
    RTIConnextDDS::cpp2_api
)

# To differentiate between debug and release builds
set_target_properties(${PROJECT_NAME}
    PROPERTIES
        DEBUG_POSTFIX "d"
)
