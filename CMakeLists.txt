CU_SET_PATH("CMAKE_MOD_INFLUXDB_DIR" "${CMAKE_CURRENT_LIST_DIR}")
CU_ADD_HOOK("AFTER_LOAD_CMAKE_MODULES" "${CMAKE_MOD_INFLUXDB_DIR}/cmake/after_load_cmake_modules.cmake")