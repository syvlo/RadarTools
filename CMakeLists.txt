cmake_minimum_required (VERSION 2.8)

project (ProjIMA)

set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall -Werror -g -ggdb " )
set ( SRC_DIR "src" )
set ( BIN_DIR "bin" )

find_package( OpenCV REQUIRED )
include_directories(/cal/homes/lobry/Programs/include/)

add_executable(${BIN_DIR}/imw2png
  ${SRC_DIR}/imw2png/main.cc
)

target_link_libraries (${BIN_DIR}/imw2png
  ${OpenCV_LIBS} SAR
)

add_executable(${BIN_DIR}/invEndianness
  ${SRC_DIR}/invEndianness/main.cc
)

target_link_libraries (${BIN_DIR}/invEndianness
  ${OpenCV_LIBS} SAR
)
