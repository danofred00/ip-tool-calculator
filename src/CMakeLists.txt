
set(CMAKE_AUTOMOC True)
set(CMAKE_AUTOUIC True)
set(CMAKE_AUTORCC True)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core Widgets Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Quick LinguistTools)

qt_standard_project_setup()

set(SOURCES
    main.cpp
    ipcalculator.h ipcalculator.cpp
    include/utilities.h
#    ui/mainwindow.h ui/mainwindow.cpp ui/mainwindow.ui
#    ui/basicframe.h ui/basicframe.cpp ui/basicframe.ui
#    ui/advancedframe.h ui/advancedframe.cpp ui/advancedframe.ui
#    ui/helpdialog.h ui/helpdialog.cpp ui/helpdialog.ui
    iptablemodel.h iptablemodel.cpp
    #ui/resources.qrc
)

#if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
# if we are running Qt6 or greater
set(ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android CACHE INTERNAL "")
qt_add_executable(IpTools MANUAL_FINALIZATION ${SOURCES})

#else()
#    # If version of Qt is 5 or lower
#    if(ANDROID)
#        add_library(IpTools SHARED ${SOURCES})
#    else()
#        add_executable(IpTools ${SOURCES})
#    endif()
#endif()

target_include_directories(IpTools PUBLIC
                           ${CMAKE_SOURCE_DIR}/lib/include
                           ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_directories(IpTools PUBLIC ${CMAKE_BINARY_DIR}/lib)
#target_link_libraries(IpTools PUBLIC ipv4 netip subnet utils)

set_target_properties(IpTools PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(IpTools PUBLIC
                      net
                      Qt${QT_VERSION_MAJOR}::Core
                      Qt${QT_VERSION_MAJOR}::Widgets
                      Qt${QT_VERSION_MAJOR}::Quick
)

# get additional files
file(GLOB_RECURSE ASSETS_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "ui/assets/*")

# add qml_module
qt_add_qml_module(IpTools
    URI "."
    VERSION 1.0
    QML_FILES
        ui/Main.qml
        ui/SubnetScreen.qml
        ui/AboutDialog.qml
        ui/BasicScreen.qml
        ui/SettingDialog.qml
        ui/components/AppDrawer.qml
        ui/components/SubnetFormComponent.qml
    RESOURCE_PREFIX "/"
    RESOURCES
        ui/qtquickcontrols2.conf
)

qt_add_resources(IpTools assets PREFIX "/" FILES ${ASSETS_FILES})

# Add translations
set(TSFILES ${CMAKE_CURRENT_SOURCE_DIR}/languages/fr_FR.ts)

set_source_files_properties(${TSFILES}
    PROPERTIES OUTPUT_LOCATION "${CMAKE_CURRENT_BINARY_DIR}/languages")
qt_add_translations(IpTools TS_FILES ${TSFILES})


install(TARGETS IpTools
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
