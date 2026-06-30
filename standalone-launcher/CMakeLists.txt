find_package(DDEShell REQUIRED)

add_library(standalone-launcher SHARED
    standalonelauncher.cpp
    standalonelauncher.h
)

target_link_libraries(standalone-launcher PRIVATE
    Dde::Shell
    launchpadcommon
)

ds_install_package(PACKAGE org.deepin.ds.launcher TARGET standalone-launcher)
ds_handle_package_translation(
    PACKAGE org.deepin.ds.launcher
    QML_FILES
    ${QML_FILES_NEED_TRANSLATION}
    ${CMAKE_CURRENT_LIST_DIR}/package/main.qml
)
