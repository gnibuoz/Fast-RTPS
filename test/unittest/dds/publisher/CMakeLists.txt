# Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

if(NOT ((MSVC OR MSVC_IDE) AND EPROSIMA_INSTALLER))
    include(${PROJECT_SOURCE_DIR}/cmake/common/gtest.cmake)
    check_gtest()
    check_gmock()

    if(GTEST_FOUND AND GMOCK_FOUND)
        find_package(Threads REQUIRED)

        set(PUBLISHERTESTS_SOURCE PublisherTests.cpp)
        set(DATAWRITERTESTS_SOURCE DataWriterTests.cpp)
        set(PUBLISHERTESTS_SOURCE PublisherTests.cpp
            ${PROJECT_SOURCE_DIR}/src/cpp/dds/pub/DataWriter.cpp
            )

        if(WIN32)
            add_definitions(-D_WIN32_WINNT=0x0601)
        endif()

        add_executable(PublisherTests ${PUBLISHERTESTS_SOURCE})
        target_compile_definitions(PublisherTests PRIVATE FASTRTPS_NO_LIB)
        target_include_directories(PublisherTests PRIVATE
            ${GTEST_INCLUDE_DIRS} ${GMOCK_INCLUDE_DIRS}
            ${PROJECT_SOURCE_DIR}/include ${PROJECT_BINARY_DIR}/include
            ${PROJECT_SOURCE_DIR}/src/cpp
            )
        target_link_libraries(PublisherTests fastrtps foonathan_memory
            ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES}
            ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})
        add_gtest(PublisherTests SOURCES ${PUBLISHERTESTS_SOURCE})

        add_executable(DataWriterTests ${DATAWRITERTESTS_SOURCE})
        target_compile_definitions(DataWriterTests PRIVATE FASTRTPS_NO_LIB)
        target_include_directories(DataWriterTests PRIVATE
            ${GTEST_INCLUDE_DIRS} ${GMOCK_INCLUDE_DIRS}
            ${PROJECT_SOURCE_DIR}/include ${PROJECT_BINARY_DIR}/include
            ${PROJECT_SOURCE_DIR}/src/cpp
            )
        target_link_libraries(DataWriterTests fastrtps foonathan_memory
            ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES}
            ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})
        add_gtest(DataWriterTests SOURCES ${DATAWRITERTESTS_SOURCE})
    endif()
endif()
