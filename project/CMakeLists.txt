cmake_minimum_required(VERSION 3.8)

if(POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif()
project(regie VERSION "1.0.0")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(MAKE_DIRECTORY build)

# Setup testing
#enable_testing()
#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIR})

# link sql lib
find_package(PostgreSQL REQUIRED)
#find_package(libpqxx REQUIRED)

# Add test cpp file
#add_executable(runUnitTests testgtest.cpp)
add_executable(regie regie.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC ${PostgreSQL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PUBLIC /usr/local/lib/libpqxx.dylib)
target_link_libraries(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/leveldb/build/libleveldb.a)
target_include_directories(${PROJECT_NAME} PUBLIC ${PostgreSQL_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC leveldb/include)

# Link test executable against gtest & gtest_main
#target_link_libraries(runUnitTests GTest::GTest GTest::Main)

#add_test(runUnitTests runUnitTests)

