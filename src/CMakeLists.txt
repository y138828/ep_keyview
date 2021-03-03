file(GLOB KEYVIEW_SOURCES *.cpp)
file(GLOB KEYVIEW_HEADERS *.hpp)

add_executable(key_view ${KEYVIEW_SOURCES} ${KEYVIEW_HEADERS})
install(TARGETS key_view DESTINATION bin COMPONENT dev)