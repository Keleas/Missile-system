QT       += core gui sql datavisualization

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = gui2
TEMPLATE = app

prj_dir = $${_PRO_FILE_PWD_}
bld_dir = $${prj_dir}/../bld
src_dir = $${prj_dir}
gui_dir = $${prj_dir}
cfg_dir = $${prj_dir}/../exec/data
res_dir = $${prj_dir}/res

INCLUDEPATH += $${src_dir}
INCLUDEPATH += $${src_dir}/csenario
INCLUDEPATH += $${src_dir}/csenario/objects_json
INCLUDEPATH += $${src_dir}/libraries


MOC_DIR     = $${bld_dir}/moc
OBJECTS_DIR = $${bld_dir}/obj
RCC_DIR     = $${bld_dir}/rcc
UI_DIR      = $${bld_dir}/gui
#MAKEFILE    = ../Makefile
DESTDIR = $${prj_dir}/../exec

CONFIG += debug_and_release with_qsqlite_driver

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win32 {
    src_dir      = $$replace(src_dir ,/,\\)
    SOURCES     += $$system("where /r $$src_dir *.c* 2> nul")
    HEADERS     += $$system("where /r $$src_dir *.h* 2> nul")
    FORMS       += $$system("where /r $$src_dir *.ui 2> nul")
} else {
    SOURCES     += $$system("find '$${src_dir}/' -name '*.c*' 2>/dev/null")
    HEADERS     += $$system("find '$${src_dir}/' -name '*.h*' 2>/dev/null")
    FORMS       += $$system("find '$${gui_dir}/' -name '*.ui' 2>/dev/null")
}

#RESOURCES += res.qrc
