
set(HEADERS
    core/metawatchprotocol.h
    core/metawatchmessage.h
    core/protocoldispatcher.h

    devicetypemessage.h
    realtimeclockmessage.h
    watchpropertyoperationmessage.h
)

if(${Qt4})
  set(QT_MOC_HDRS
    
  )
  qt4_wrap_cpp(MOC_OUTFILES ${QT_MOC_HEADERS})
endif(${Qt4})

set(QT_SRCS
    core/metawatchprotocol.cpp
    core/metawatchmessage.cpp
    core/protocoldispatcher.cpp

    devicetypemessage.cpp
    realtimeclockmessage.cpp
    watchpropertyoperationmessage.cpp
    controlfullscreenmessage.cpp
    writelcdbuffermessage.cpp
    setwidgetlistmessage.cpp
    widget.cpp
    page.cpp
    screen.cpp
    normalwidget.cpp
    clockwidget.cpp
    widgetpayload.cpp
)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/config.h"
  )

add_library(qmwprotocol STATIC ${QT_SRCS} ${MOC_OUTFILES})

if(${Qt4})
  target_link_libraries(qmwprotocol ${QT_LIBRARIES} ${Boost_LIBRARIES})
else(${Qt4})
  target_link_libraries(qmwprotocol Qt5::Core ${Boost_LIBRARIES})
endif(${Qt4})

set_target_properties(qmwprotocol PROPERTIES
  PUBLIC_HEADER "${HEADERS}")
  
install(TARGETS qmwprotocol
  # IMPORTANT: Add the qmwprotocol library to the "export-set"
  EXPORT QMWProtocolTargets
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR}" COMPONENT dev
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}" COMPONENT dev)
  
