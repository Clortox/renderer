file(GLOB OBJ_FILES CONFIGURE_DEPENDS "*.obj")

foreach(OBJ_FILE ${OBJ_FILES})
    get_filename_component(TEST_NAME ${OBJ_FILE} NAME_WE)
    add_test(
        NAME ${TEST_NAME}
        COMMAND renderer ${OBJ_FILE}
    )
endforeach()
