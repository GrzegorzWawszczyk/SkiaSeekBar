add_library(SkiaSeekBar SHARED
    main.cpp
)

target_link_libraries(SkiaSeekBar PRIVATE core)


set(ANDROID_GRADLE_SRC "${CMAKE_CURRENT_SOURCE_DIR}/gradle")
set(ANDROID_GRADLE_DST "${CMAKE_BINARY_DIR}/../apk")

message(STATUS "Copying Gradle project to ${ANDROID_GRADLE_DST}")
file(COPY "${ANDROID_GRADLE_SRC}/" DESTINATION "${ANDROID_GRADLE_DST}")