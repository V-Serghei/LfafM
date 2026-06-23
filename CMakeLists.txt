cmake_minimum_required(VERSION 3.20)
project(LFaf LANGUAGES CXX)

include(CTest)

add_library(lfaf_core
        src/RegularLanguage.cpp
        include/lfaf/RegularLanguage.h
)

target_include_directories(lfaf_core PUBLIC include)
target_compile_features(lfaf_core PUBLIC cxx_std_20)

add_executable(LFaf
        src/main.cpp
)

target_include_directories(LFaf PRIVATE include)
target_link_libraries(LFaf PRIVATE lfaf_core)

if(BUILD_TESTING)
    add_executable(regular_language_tests
            tests/regular_language_tests.cpp
    )

    target_link_libraries(regular_language_tests PRIVATE lfaf_core)

    add_test(NAME regular_language_tests COMMAND regular_language_tests)
endif()
