set(__ON FALSE)
if (__ON)
    add_executable(DotNamespaceLeak DotNamespaceLeak.cpp)

    target_link_libraries(DotNamespaceLeak PRIVATE
            $<TARGET_FILE:redland-combined>
            ${LINK_LIBRARIES})
    TARGET_INCLUDE_DIRECTORIES(DotNamespaceLeak PRIVATE ${INCLUDE_DIRS})
endif ()