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

DEFINES += V_GMTIME_SAFE=gmtime_r

SOURCES += \
    blueprint.cpp \
    blueprint_book.cpp \
    bprint_landfill.cpp \
    blueprint_io.cpp \
    calc_lazy_bastard.cpp \
    clipboard.cpp \
    deconstruction_planner.cpp \
    entity.cpp \
    items/arithmetic_combinator.cpp \
    items/assembling_machine.cpp \
    items/chests.cpp \
    items/constant_combinator.cpp \
    item.cpp \
    items/control_behavior.cpp \
    items/decider_combinator.cpp \
    items/icons.cpp \
    items/inserter.cpp \
    items/trains.cpp \
    json.cpp \
    landfill_from_clipboard.cpp \
    main.cpp \
    mainwindow.cpp \
    preparations/pr_assemble_tmpl.cpp \
    preparations/pr_basic_features_st2.cpp \
    preparations/pr_burn_prod_green_as_is.cpp \
    preparations/pr_chests.cpp \
    preparations/pr_descructors.cpp \
    preparations/pr_fluid_coalstation.cpp \
    preparations/pr_fluids.cpp \
    preparations/pr_logistic_templates.cpp \
    preparations/pr_old_templates_as_is.cpp \
    preparations/pr_science_before_rocket.cpp \
    preparations/pr_science_imported_nb.cpp \
    preparations/pr_trains_v2.cpp \
    preparations/pr_uran.cpp \
    preparations/pr_war_assemblies.cpp \
    preparations/pr_zero_book_as_is.cpp \
    prototypes.cpp \
    recipe.cpp \
    v2-books/assemblies_before_drons.cpp \
    v2-books/city_blocks.cpp \
    v2-books/electricity.cpp \
    v2-books/furnaces.cpp \
    v2-books/intermediate_production_l1.cpp \
    v2-books/mining.cpp \
    v2-books/assemble/recipe_maker.cpp \
    v2-books/oil_refinery.cpp \
    v2-books/science.cpp \
    v2-books/tier0.cpp \
    v2-books/train_stations.cpp \
    v2-books/warehouse.cpp

HEADERS += \
    blueprint.h \
    blueprint_book.h \
    bprint_landfill.h \
    blueprint_io.h \
    calc_lazy_bastard.h \
    clipboard.h \
    deconstruction_planner.h \
    entity.h \
    items/arithmetic_combinator.h \
    items/assembling_machine.h \
    items/chests.h \
    items/constant_combinator.h \
    item.h \
    items/control_behavior.h \
    items/decider_combinator.h \
    items/icons.h \
    items/inserter.h \
    items/trains.h \
    json.h \
    landfill_from_clipboard.h \
    mainwindow.h \
    names.h \
    preparations/pr_assemble_tmpl.h \
    preparations/pr_basic_features_st2.h \
    preparations/pr_burn_prod_green_as_is.h \
    preparations/pr_chests.h \
    preparations/pr_descructors.h \
    preparations/pr_fluid_coalstation.h \
    preparations/pr_fluids.h \
    preparations/pr_logistic_templates.h \
    preparations/pr_old_templates_as_is.h \
    preparations/pr_science_before_rocket.h \
    preparations/pr_science_imported_nb.h \
    preparations/pr_trains_v2.h \
    preparations/pr_uran.h \
    preparations/pr_war_assemblies.h \
    preparations/pr_zero_book_as_is.h \
    prototypes.h \
    recipe.h \
    qdeb.h \
    v2-books/assemble/raw_assembling_machines.h \
    v2-books/assemble/raw_belts_l3_assemble.h \
    v2-books/assemble/raw_chests.h \
    v2-books/assemble/raw_drons.h \
    v2-books/assemble/raw_engine_heads.h \
    v2-books/assemble/raw_equipment.h \
    v2-books/assemble/raw_logistics.h \
    v2-books/assemble/raw_manipulators.h \
    v2-books/assemble/raw_poles.h \
    v2-books/assemble/raw_six_advanced_circuits.h \
    v2-books/assemblies_before_drons.h \
    v2-books/city_blocks.h \
    v2-books/electricity.h \
    v2-books/furnaces.h \
    v2-books/intermediate_production_l1.h \
    v2-books/mining.h \
    v2-books/assemble/recipe_maker.h \
    v2-books/oil_refinery.h \
    v2-books/raw_city_blocks.h \
    v2-books/raw_electricity.h \
    v2-books/raw_furnances.h \
    v2-books/raw_oil.h \
    v2-books/raw_oil_refinery.h \
    v2-books/raw_science.h \
    v2-books/raw_tier0.h \
    v2-books/raw_train_stations.h \
    v2-books/raw_warehouse.h \
    v2-books/science.h \
    v2-books/tier0.h \
    v2-books/train_stations.h \
    v2-books/warehouse.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

VLIBS_DIR = $$PWD/vlibs2
include( $$VLIBS_DIR/vlog/vlog.pri )
include( $$VLIBS_DIR/vbyte_buffer/vbyte_buffer.pri )
