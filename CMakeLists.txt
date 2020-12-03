cmake_minimum_required(VERSION 3.17)

project(helloCMake)

set(EXECUTABLE MemoryAnalyzer)



add_executable(${EXECUTABLE})
add_subdirectory(src)

# fmt
add_subdirectory(lib/fmt)
target_include_directories(${EXECUTABLE} PUBLIC lib/fmt/include)
target_link_libraries(${EXECUTABLE} fmt)

# libFort
set(FORT_ENABLE_TESTING OFF CACHE INTERNAL "")
add_subdirectory(lib/libfort)
target_include_directories(${EXECUTABLE} PUBLIC lib/libfort/lib)
target_link_libraries(${EXECUTABLE} fort)


configure_file(tttestLC.elf tttestLC.elf COPYONLY)
configure_file(tttest32.elf tttest32.elf COPYONLY)
configure_file(tttest36.elf tttest36.elf COPYONLY)
configure_file(tttest40.elf tttest40.elf COPYONLY)
configure_file(ttt.sym ttt.sym COPYONLY)


install(TARGETS ${EXECUTABLE} DESTINATION bin)
