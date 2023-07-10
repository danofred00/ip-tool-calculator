
set(CMAKE_AUTOMOC True)
set(CMAKE_AUTOUIC True)
set(CMAKE_AUTORCC True)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core Widgets Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Quick)

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
    ui/resources.qrc
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
                      Qt${QT_VERSION_MAJOR}::Quick)

install(TARGETS IpTools
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
