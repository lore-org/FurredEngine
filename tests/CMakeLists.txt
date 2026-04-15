macro (add_fe_test name)
    add_executable("fe_tests_${name}")

    target_sources("fe_tests_${name}" PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/${name}.c
    )

    target_link_libraries("fe_tests_${name}" PUBLIC FurredEngine)
endmacro()

add_fe_test(window)