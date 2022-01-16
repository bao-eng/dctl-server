set(SOURCES dctl_server.cpp
            dctl_engine.h
            dctl_engine.cpp
            server.h
            server.cpp
            udp_server.h
            udp_server.cpp
            ./dctl-common/src/dctl_common.h
            ./dctl-common/src/dctl_common.cpp
            ./dctl-common/src/dctl_message_generated.h)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
