cmake_minimum_required(VERSION 3.30)
project(zeta)

set(ZETA_VERSION "0.1.0")

set(CMAKE_CXX_STANDARD 20)
add_library(zeta STATIC
        test/integer/main.cpp
)

target_sources(zeta
        PUBLIC
        FILE_SET CXX_MODULES
        FILES
        src/modules/zeta.ixx
        src/modules/ooga/integer.ixx
        src/modules/ooga/fixed_decimal.ixx
        src/modules/optional.ixx
        src/modules/config.ixx



)
add_executable(zeta_integer_test
        test/integer/main.cpp
)

target_link_libraries(zeta_integer_test PRIVATE zeta)

add_executable(zeta_fixed_decimal_test
        test/fixed_decimal/main.cpp
)

target_link_libraries(zeta_fixed_decimal_test PRIVATE zeta)


add_executable(zeta_optional_test
        test/optional/main.cpp
)

target_link_libraries(zeta_optional_test PRIVATE zeta)

