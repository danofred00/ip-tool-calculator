
set(CMAKE_AUTOMOC True)
set(CMAKE_AUTOUIC True)
set(CMAKE_AUTORCC True)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

set(SOURCES
    main.cpp
    include/utilities.h
    ui/mainwindow.h ui/mainwindow.cpp ui/mainwindow.ui
    ui/basicframe.h ui/basicframe.cpp ui/basicframe.ui
    ui/advancedframe.h ui/advancedframe.cpp ui/advancedframe.ui
    ui/iptablemodel.h ui/iptablemodel.cpp
)

add_executable(IpTools WIN32 MACOSX_BUNDLE ${SOURCES})
target_include_directories(IpTools PUBLIC
                           ${CMAKE_SOURCE_DIR}/lib/include
                           ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_directories(IpTools PUBLIC ${CMAKE_BINARY_DIR}/lib)
#target_link_libraries(IpTools PUBLIC ipv4 netip subnet utils)

target_link_libraries(IpTools PUBLIC
                      net
                      Qt${QT_VERSION_MAJOR}::Core
                      Qt${QT_VERSION_MAJOR}::Widgets)
                    
install(TARGETS IpTools LIBRARY DESTINATION ${CMAKE_INSTALL_BINDIR})