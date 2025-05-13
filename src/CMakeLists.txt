find_package(PkgConfig REQUIRED)

pkg_check_modules(ZLIB REQUIRED zlib)

set(HEADER_LIST "${tutorial_zlib_SOURCE_DIR}/include/tutorial_zlib/lib.hpp")

add_library(tutorial_zlib_core lib.cpp ${HEADER_LIST})
target_include_directories(tutorial_zlib_core PUBLIC ../include)

target_link_libraries(tutorial_zlib_core ${ZLIB_LIBRARIES})
target_include_directories(tutorial_zlib_core PUBLIC ${ZLIB_INCLUDE_DIRS})
target_compile_options(tutorial_zlib_core PUBLIC ${ZLIB_CFLAGS_OTHER})


# IDEs should put the headers in a nice place
source_group(
  TREE "${tutorial_zlib_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
