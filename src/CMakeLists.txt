add_library(jumanppy SHARED main.cc)
# add_executable(jumanppy main.cc)
set_target_properties(jumanppy PROPERTIES OUTPUT_NAME "jumanppy")
target_link_libraries(jumanppy jpp_core)