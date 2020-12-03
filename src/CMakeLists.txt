target_sources (${EXECUTABLE} PRIVATE
  main.cpp
  helpers.cpp
  objDumpParser.cpp
)

add_subdirectory(Analyzers)

