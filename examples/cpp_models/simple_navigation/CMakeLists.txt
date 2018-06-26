cmake_minimum_required(VERSION 2.8.3)

add_executable("${PROJECT_NAME}_simple_navigation"
  src/simple_navigation.cpp
  src/main.cpp
)
target_link_libraries("${PROJECT_NAME}_simple_navigation"
  "${PROJECT_NAME}"
)
install(TARGETS "${PROJECT_NAME}_simple_navigation"
  RUNTIME DESTINATION "${BINARY_INSTALL_PATH}"
)