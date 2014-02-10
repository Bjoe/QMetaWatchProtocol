
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
)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/config.h"
  )

add_library(qmwmprotocol STATIC ${QT_SRCS} ${MOC_OUTFILES})

if(${Qt4})
  target_link_libraries(qmwmprotocol ${QT_LIBRARIES} ${Boost_LIBRARIES})
else(${Qt4})
  target_link_libraries(qmwmprotocol Qt5::Core ${Boost_LIBRARIES})
endif(${Qt4})
