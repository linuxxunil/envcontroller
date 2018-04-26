TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    at_settings.cpp \
    at_controller.cpp \
    at_application.cpp \
    at_work_thread.cpp \
    at_logger.cpp \
    web/app/at_web_thread.cpp \
    web/app/controller/at_dumpcontroller.cpp \
    web/app/at_response_code.cpp \
    web/app/at_http_routing.cpp \
    at_system.cpp \
    web/app/controller/at_service_users.cpp \
    web/app/controller/at_service_system.cpp \
    web/app/controller/at_service_interface.cpp

HEADERS += \
    at_settings.h \
    at_controller.h \
    at_application.h \
    at_work_thread.h \
    at_logger.h \
    web/app/at_web_thread.h \
    web/app/controller/at_dumpcontroller.h \
    web/app/at_response_code.h \
    web/app/at_http_routing.h \
    at_system.h \
    web/app/controller/at_service_users.h \
    web/app/controller/at_service_system.h \
    web/app/controller/at_service_interface.h

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
include(deployment.pri)
include(./web/core/logging/logging.pri)
include(./web/core/httpserver/httpserver.pri)
include(./web/core/templateengine/templateengine.pri)
include(./web/core/qtservice/qtservice.pri)



