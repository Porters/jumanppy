# add_library(jumanpp SHARED main.cc)
add_executable(jumanpp main.cc)
set_target_properties(jumanpp PROPERTIES OUTPUT_NAME "jumanpp")
target_link_libraries(jumanpp jpp_core)