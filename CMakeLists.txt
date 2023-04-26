cmake_minimum_required(VERSION 3.10)


project(
    Utils

    LANGUAGES
        ASM
        C
        CXX
)

add_library (
    ${PROJECT_NAME}

    Src/event_queue.c
    Src/schedule.c
    Src/task.c
    Src/crc.c
)

target_include_directories(
    ${PROJECT_NAME}
    
    PUBLIC
        Inc
)

target_compile_features(
    ${PROJECT_NAME}
    
    PUBLIC
        cxx_std_17
        c_std_11
)


target_link_libraries(
    ${PROJECT_NAME}

    PUBLIC
        c 
        m 
        nosys
)
