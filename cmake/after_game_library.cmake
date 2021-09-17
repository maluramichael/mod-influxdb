find_package(CURL REQUIRED)

set(PUBLIC_INCLUDES
    ${PUBLIC_INCLUDES}
    ${CURL_INCLUDE_DIR}
)

target_include_directories(
    game-interface
    INTERFACE
    ${PUBLIC_INCLUDES}
)

target_link_libraries(
    game
    PUBLIC
    curl
)
