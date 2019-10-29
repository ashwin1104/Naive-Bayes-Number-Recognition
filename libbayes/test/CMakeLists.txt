add_executable(libbayes-tests
        main.cpp test-validate.cpp test-training.cpp test-classification.cpp test-image.cpp
        test-validate.cpp ../src/validate-file.cpp)
target_include_directories(libbayes-tests PRIVATE ./)

target_link_libraries(libbayes-tests libbayes)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang"
        OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    target_compile_options(libbayes-tests PRIVATE
            -Wall
            -Wextra
            -Wswitch
            -Wconversion
            -Wparentheses
            -Wfloat-equal
            -Wzero-as-null-pointer-constant
            -Wpedantic
            -pedantic
            -pedantic-errors)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    target_compile_options(libbayes-tests PRIVATE
            /W3)
endif ()