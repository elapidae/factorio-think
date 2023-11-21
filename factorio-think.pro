QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    blueprint.cpp \
    blueprint_book.cpp \
    bprint_landfill.cpp \
    blueprint_io.cpp \
    clipboard.cpp \
    deconstruction_planner.cpp \
    items/arithmetic_combinator.cpp \
    items/assembler_machines.cpp \
    items/constant_combinator.cpp \
    item.cpp \
    items/decider_combinator.cpp \
    items/icons.cpp \
    items/inserter.cpp \
    items/trains.cpp \
    json.cpp \
    main.cpp \
    mainwindow.cpp \
    make_books.cpp \
    preparations/pr_assemble_tmpl.cpp \
    preparations/pr_burn_prod_green_as_is.cpp \
    preparations/pr_descructors.cpp \
    preparations/pr_fluid_coalstation.cpp \
    preparations/pr_fluids.cpp \
    preparations/pr_science_before_rocket.cpp \
    preparations/pr_trains_v2.cpp \
    preparations/pr_uran.cpp \
    preparations/pr_zero_book_as_is.cpp \
    prototypes.cpp \
    recipe.cpp

HEADERS += \
    blueprint.h \
    blueprint_book.h \
    bprint_landfill.h \
    blueprint_io.h \
    clipboard.h \
    deconstruction_planner.h \
    items/arithmetic_combinator.h \
    items/assembler_machines.h \
    items/constant_combinator.h \
    item.h \
    items/decider_combinator.h \
    items/icons.h \
    items/inserter.h \
    items/trains.h \
    json.h \
    mainwindow.h \
    make_books.h \
    names.h \
    preparations/pr_assemble_tmpl.h \
    preparations/pr_burn_prod_green_as_is.h \
    preparations/pr_descructors.h \
    preparations/pr_fluid_coalstation.h \
    preparations/pr_fluids.h \
    preparations/pr_science_before_rocket.h \
    preparations/pr_trains_v2.h \
    preparations/pr_uran.h \
    preparations/pr_zero_book_as_is.h \
    prototypes.h \
    recipe.h \
    qdeb.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

VLIBS_DIR = $$PWD/vlibs2
include( $$VLIBS_DIR/vlog/vlog.pri )
include( $$VLIBS_DIR/vbyte_buffer/vbyte_buffer.pri )
