cmake_minimum_required(VERSION 2.8.3)

add_executable("${PROJECT_NAME}_navigation_monitor"
  src/navigation_monitor.cpp
  src/main.cpp
)
target_link_libraries("${PROJECT_NAME}_navigation_monitor"
  "${PROJECT_NAME}"
)
install(TARGETS "${PROJECT_NAME}_navigation_monitor"
  RUNTIME DESTINATION "${BINARY_INSTALL_PATH}"
)