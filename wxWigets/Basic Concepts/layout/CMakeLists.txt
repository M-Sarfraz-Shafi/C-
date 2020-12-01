cmake_minimum_required(VERSION 2.8.12)

project(layout)
find_package(wxWidgets 3.1 COMPONENTS core base aui REQUIRED)
include(${wxWidgets_USE_FILE})
message($)
set(SRC_FILES
    sizer_GridSizer.cpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
