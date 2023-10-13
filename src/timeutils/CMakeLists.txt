file (GLOB TIMEUTILS_HEADERS "*.h")
file (GLOB TIMEUTILS_SOURCES "*.cpp")

message(STATUS "header files:" ${TIMEUTILS_HEADERS})
message(STATUS "source files:" ${TIMEUTILS_SOURCES})

source_group("headers" FILES ${TIMEUTILS_HEADERS})
source_group("sources" FILES ${TIMEUTILS_SOURCES})

include_directories (.)

add_library(timeutils SHARED ${TIMEUTILS_HEADERS} ${TIMEUTILS_SOURCES})
add_library(timeutils_static STATIC ${TIMEUTILS_HEADERS} ${TIMEUTILS_SOURCES})

set_property(TARGET timeutils PROPERTY FOLDER ${PRJECT_LIBRARIES_DIR})
set_property(TARGET timeutils_static PROPERTY FOLDER ${PRJECT_LIBRARIES_DIR})
target_include_directories(timeutils_static PUBLIC ".")
#target_link_libraries(timeutils_static PUBLIC type_traits)

install (TARGETS timeutils
         RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/_install
         LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/_install
)
