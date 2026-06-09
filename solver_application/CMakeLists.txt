add_executable(solver_application equation.cpp)

target_include_directories(solver_application PRIVATE
  ${PROJECT_SOURCE_DIR}/formatter_ex_lib
  ${PROJECT_SOURCE_DIR}/solver_lib
)

target_link_libraries(solver_application PRIVATE formatter_ex solver)

install(TARGETS solver_application
  RUNTIME DESTINATION bin
)
