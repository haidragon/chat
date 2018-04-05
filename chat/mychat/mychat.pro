#-------------------------------------------------
#
# Project created by QtCreator 2018-03-31T07:48:29
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mychat
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        dialog.cpp \
    ccmychardialog.cpp \
    personlistbuddy.cpp \
    personlist.cpp \
    spingserver.cpp \
    camaraget.cpp \
    camthread.cpp \
    sendmainwindow.cpp \
    receivemainwindow.cpp

HEADERS  += dialog.h \
    ccmychardialog.h \
    personlistbuddy.h \
    personlist.h \
    spingserver.h \
    camaraget.h \
    camthread.h \
    sendmainwindow.h \
    receivemainwindow.h

FORMS    += dialog.ui \
    ccmychardialog.ui \
    spingserver.ui \
    camaraget.ui \
    sendmainwindow.ui \
    receivemainwindow.ui

RESOURCES += \
    image.qrc
macx{
 INCLUDEPATH += /usr/local/opt/opencv@3/include
LIBS += -L/usr/local/Cellar/opencv/3.4.1/lib -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib  -lopencv_dnn -lopencv_dpm -lopencv_fuzzy -lopencv_line_descriptor -lopencv_optflow -lopencv_plot -lopencv_reg -lopencv_saliency -lopencv_stereo -lopencv_structured_light -lopencv_rgbd -lopencv_surface_matching -lopencv_tracking -lopencv_datasets -lopencv_text -lopencv_face -lopencv_xfeatures2d -lopencv_shape -lopencv_video -lopencv_ximgproc -lopencv_calib3d -lopencv_features2d -lopencv_flann -lopencv_xobjdetect -lopencv_objdetect -lopencv_ml -lopencv_xphoto -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_photo -lopencv_imgproc -lopencv_core
}
