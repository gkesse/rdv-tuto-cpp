include(FetchContent)
set(SEAL_LAKE_VERSION v0.2.0)
set(FETCHCONTENT_QUIET FALSE)
FetchContent_Declare(seal_lake_${SEAL_LAKE_VERSION}
    SOURCE_DIR seal_lake_${SEAL_LAKE_VERSION}
    GIT_REPOSITORY "https://github.com/kamchatka-volcano/seal_lake.git"
    GIT_TAG ${SEAL_LAKE_VERSION}
)
FetchContent_MakeAvailable(seal_lake_${SEAL_LAKE_VERSION})
include(${seal_lake_${SEAL_LAKE_VERSION}_SOURCE_DIR}/seal_lake.cmake)

SealLake_Import(cmdlime 2.7.0
        GIT_REPOSITORY https://github.com/kamchatka-volcano/cmdlime
        GIT_TAG v2.7.0
)

SealLake_Import(sfun 5.1.0
        GIT_REPOSITORY https://github.com/kamchatka-volcano/sfun
        GIT_TAG v5.1.0
)
