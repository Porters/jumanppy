add_library(jumanppy SHARED main.cc)
set_target_properties(jumanppy PROPERTIES OUTPUT_NAME "jumanppy")
target_link_libraries(jumanppy jpp_core)

add_executable(jumanppyexe main.cc)
set_target_properties(jumanppyexe PROPERTIES OUTPUT_NAME "jumanppy")
target_link_libraries(jumanppyexe jpp_core)