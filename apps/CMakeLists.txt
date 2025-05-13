# Testing library
FetchContent_Declare(
  cxxopts
  GIT_REPOSITORY https://github.com/jarro2783/cxxopts
  GIT_TAG v3.2.0)
FetchContent_MakeAvailable(cxxopts)


add_executable(app app.cpp)

target_link_libraries(app 
    PRIVATE tutorial_zlib_core
    PRIVATE cxxopts::cxxopts)
