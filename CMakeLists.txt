cmake_minimum_required(VERSION 3.20)
project(UKOOA_PARSER)

add_executable(${PROJECT_NAME} 
    main.cpp 
    AppSettings.cpp 
    Ukooaparser.cpp 
    JsonWriter.cpp   
    Ukooa.cpp)

find_package(Git QUIET)

if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE "Check submodules during build" ON)

    if(GIT_SUBMODULE)
        message(STATUS "Updating submodules...")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE GIT_SUBMOD_RESULT)
        
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/jsoncpp/CMakeLists.txt")
    message(FATAL_ERROR "JSONCPP could not be downloaded.")
endif()

add_subdirectory(external/jsoncpp)

target_include_directories(${PROJECT_NAME} 
    PUBLIC external/jsoncpp/include
    PUBLIC ${EXTRA_INC_DIRS})

target_link_directories(${PROJECT_NAME}
    PRIVATE external/jsoncpp/src)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE ${EXTRA_LINKS}
    PRIVATE jsoncpp)
