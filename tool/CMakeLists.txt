cmake_minimum_required(VERSION 3.16)

project(tool VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES tool_vi_VN.ts)

# --- KHAI BÁO TẤT CẢ FILE CỦA DỰ ÁN TẠI ĐÂY ---
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        res.qrc                  # File tài nguyên ảnh
        bfnpreviewwidget.cpp     # File code Preview
        bfnpreviewwidget.h       # File header Preview
        TranslationData.h        # File cấu trúc dữ liệu
        translationmodel.cpp     # File code Model
        translationmodel.h       # File header Model
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(tool
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        bmghandler.h bmghandler.cpp
        rarchandler.h rarchandler.cpp
        yaz0.h yaz0.cpp       # Chỉ cần gọi biến này là đủ
    )

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(tool SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(tool
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(tool PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

target_include_directories(tool PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Qt for iOS/MacOS settings
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.tool)
endif()
set_target_properties(tool PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS tool
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(tool)
endif()
