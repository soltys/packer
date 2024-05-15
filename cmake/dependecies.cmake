include(FetchContent)

#### START TOOLS
FetchContent_Declare(
  embed_resource
  GIT_REPOSITORY https://github.com/soltys/embed-resource.git
  GIT_TAG        0.2.0
)
FetchContent_MakeAvailable(embed_resource)
set_target_properties(embed_resource PROPERTIES FOLDER "Dependencies")
#### END TOOLS

#### START Third Party
set(SQLITECPP_RUN_CPPLINT OFF CACHE BOOL "" FORCE)
set(SQLITECPP_RUN_CPPCHECK OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
  SQLiteCpp
  GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
  GIT_TAG        3.3.1
  EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(SQLiteCpp)
set_target_properties(SQLiteCpp PROPERTIES FOLDER "Dependencies")
set_target_properties(sqlite3 PROPERTIES FOLDER "Dependencies")