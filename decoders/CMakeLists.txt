file(GLOB SOURCES src/*.cc)
file(GLOB HEADERS include/*.hh)

add_library(decoders STATIC ${SOURCES} ${HEADERS})
target_include_directories(decoders PUBLIC include)

target_link_libraries(decoders PUBLIC writer config global plotter writer ${ROOT_LIBRARIES})