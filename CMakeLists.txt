cmake_minimum_required(VERSION 3.10)

include("cmake/HunterGate.cmake")
HunterGate(
  URL "https://github.com/cpp-pm/hunter/archive/v0.23.251.tar.gz"
  SHA1 "5659b15dc0884d4b03dbd95710e6a1fa0fc3258d"
  LOCAL
)

project(lab08 LANGUAGES CXX)

set(LAB08_VERSION_MAJOR 0)
set(LAB08_VERSION_MINOR 1)
set(LAB08_VERSION_PATCH 0)
set(LAB08_VERSION_TWEAK 0)
set(LAB08_VERSION
  ${LAB08_VERSION_MAJOR}.${LAB08_VERSION_MINOR}.${LAB08_VERSION_PATCH}.${LAB08_VERSION_TWEAK}
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build unit tests" ON)

add_subdirectory(formatter_lib)
add_subdirectory(formatter_ex_lib)
add_subdirectory(solver_lib)
add_subdirectory(hello_world_application)
add_subdirectory(solver_application)
add_subdirectory(banking)

if(BUILD_TESTS)
  hunter_add_package(GTest)
  find_package(GTest CONFIG REQUIRED)

  enable_testing()
  add_executable(check
    tests/account_test.cpp
    tests/transaction_test.cpp
  )
  target_link_libraries(check PRIVATE banking GTest::main GTest::gmock)
  add_test(NAME check COMMAND check)
endif()

add_executable(demo ${CMAKE_CURRENT_SOURCE_DIR}/demo/main.cpp)
target_include_directories(demo PRIVATE
  ${PROJECT_SOURCE_DIR}/formatter_lib
)
target_link_libraries(demo PRIVATE formatter)

install(TARGETS demo
  RUNTIME DESTINATION bin
)

include(CPackConfig.cmake)
