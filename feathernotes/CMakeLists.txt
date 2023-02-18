set(QT5_MINIMUM_VERSION "5.15.0")
set(QT6_MINIMUM_VERSION "6.3.0")
set(HUNSPELL_MINIMUM_VERSION "1.6")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(QT_VERSION_MAJOR 5)
find_package(Qt5 "${QT5_MINIMUM_VERSION}" REQUIRED COMPONENTS Core Gui Widgets Svg Xml Network PrintSupport DBus)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
                      ${Qt5Core_INCLUDE_DIRS}
                      ${Qt5Gui_INCLUDE_DIRS}
                      ${Qt5Widgets_INCLUDE_DIRS}
                      ${Qt5Svg_INCLUDE_DIRS}
                      ${Qt5Xml_INCLUDE_DIRS}
                      ${Qt5Network_INCLUDE_DIRS}
                      ${Qt5PrintSupport_INCLUDE_DIRS}
                      ${Qt5DBus_INCLUDE_DIRS})

add_definitions(-DDATADIR="${CMAKE_INSTALL_PREFIX}/share")

set(feathernotes_SRCS
    main.cpp
    singleton.cpp
    signalDaemon.cpp
    colorLabel.cpp
    fn.cpp
    find.cpp
    domitem.cpp
    dommodel.cpp
    lineedit.cpp
    pref.cpp
    textedit.cpp
    simplecrypt.cpp
    vscrollbar.cpp
    printing.cpp
    svgicons.cpp)

set(feathernotes_RESOURCES data/fn.qrc)
set(METAINFO_FILE data/feathernotes.metainfo.xml)
set(XML_FILE data/feathernotes.xml)


if(CMAKE_VERSION VERSION_LESS "3.10.0") # CMP0071 in 3.10: Let AUTOMOC and AUTOUIC process GENERATED files
    qt5_wrap_cpp(EXTRA_HEADERS warningbar.h spinbox.h messagebox.h filedialog.h help.h settings.h treeview.h treedelegate.h)
else()
    set(EXTRA_HEADERS warningbar.h spinbox.h messagebox.h filedialog.h help.h settings.h treeview.h treedelegate.h)
endif()

# translations
if(Qt${QT_VERSION_MAJOR}LinguistTools_FOUND)
  file(GLOB TS_FILES data/translations/feathernotes_*.ts)
    qt5_add_translation(QM_FILES ${TS_FILES})
  add_executable(feathernotes ${feathernotes_SRCS} ${feathernotes_DBUS_SRCS} ${feathernotes_RESOURCES} ${EXTRA_HEADERS} ${DESKTOP_FILE} ${QM_FILES})
  install(FILES ${QM_FILES} DESTINATION "${CMAKE_INSTALL_PREFIX}/share/feathernotes/translations")
else(Qt${QT_VERSION_MAJOR}LinguistTools_FOUND)
  add_executable(feathernotes ${feathernotes_SRCS} ${feathernotes_DBUS_SRCS} ${feathernotes_RESOURCES} ${EXTRA_HEADERS} ${DESKTOP_FILE})
endif(Qt${QT_VERSION_MAJOR}LinguistTools_FOUND)

target_link_libraries(feathernotes ${Qt5Core_LIBRARIES}
                                     ${Qt5Gui_LIBRARIES}
                                     ${Qt5Widgets_LIBRARIES}
                                     ${Qt5Svg_LIBRARIES}
                                     ${Qt5Xml_LIBRARIES}
                                     ${Qt5Network_LIBRARIES}
                                     ${Qt5PrintSupport_LIBRARIES}
                                     ${Qt5DBus_LIBRARIES})
