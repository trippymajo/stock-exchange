#Find
FIND_PACKAGE(Boost 1.40 COMPONENTS system REQUIRED)
FIND_PACKAGE(Threads REQUIRED)
FIND_PACKAGE(Qt5 COMPONENTS Widgets REQUIRED)

# Variables
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTORCC ON)
SET(SOURCES
ClientMain.cpp
TcpClient.cpp
Registration/Register.cpp
)
SET(HEADERS
TcpClient.h
Registration/Register.h
)

#Exe
ADD_EXECUTABLE(Client ${SOURCES} ${HEADERS})

#Include
TARGET_INCLUDE_DIRECTORIES(Client PRIVATE ${Boost_INCLUDE_DIR})
TARGET_INCLUDE_DIRECTORIES(Client PRIVATE ${PROJECT_SOURCE_DIR}/Common/)
TARGET_INCLUDE_DIRECTORIES(Client PRIVATE ${PROJECT_SOURCE_DIR}/Client/)
TARGET_INCLUDE_DIRECTORIES(Client PRIVATE ${PROJECT_SOURCE_DIR}/Client/Registration/)

#Link
TARGET_LINK_LIBRARIES(Client PRIVATE Threads::Threads ${Boost_LIBRARIES} Qt::Widgets)