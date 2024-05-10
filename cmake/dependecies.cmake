include(FetchContent)

#### START TOOLS
FetchContent_Declare(
  embed_resource
  GIT_REPOSITORY https://github.com/soltys/embed-resource.git
  GIT_TAG        0.2.0
)
FetchContent_MakeAvailable(embed_resource)
set_target_properties(embed_resource PROPERTIES FOLDER "Tools")
#### END TOOLS

#### START Third Party
FetchContent_Declare(
  SQLiteCpp
  GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
  GIT_TAG        3.3.1
  EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(SQLiteCpp)
set_target_properties(SQLiteCpp PROPERTIES FOLDER "Dependencies")
set_target_properties(sqlite3 PROPERTIES FOLDER "Dependencies")