
if(CMAKE_CROSSCOMPILING)
    include(Coverage)
endif(CMAKE_CROSSCOMPILING)

set(CMAKE_AUTOMOC OFF)

if(${Qt4})
  find_package(Qt4 4.7.1  REQUIRED QtTest QtSql)
  include(${QT_USE_FILE})
else(${Qt4})
  # cmake example from http://qt-project.org/doc/qt-5.1/qtdoc/cmake-manual.html
  find_package(Qt5Test REQUIRED)
endif(${Qt4})

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/testconfig.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/testconfig.h"
  )

include_directories(
  "../src" 
  "${CMAKE_CURRENT_BINARY_DIR}/../src"
)

set(test_additional_lib
    qmwmprotocol
)

#set(test_additional
#    foo.cpp
#)

qt_test(foo exampletest.cpp)
qt_test(MetaWatchProtocol metawatchprotocoltest.cpp)
qt_test(DeviceTypeMessage devicetypemessagetest.cpp)
qt_test(RealTimeClockMessage realtimeclockmessagetest.cpp)
qt_test(WatchPropertyOperatonMessage watchpropertyoperationmessagetest.cpp)
qt_test(Protocol protocoltest.cpp)
qt_test(ProtocolDispatcher protocoldispatchertest.cpp)
