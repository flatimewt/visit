# DO NOT EDIT THIS FILE! THIS FILE IS AUTOMATICALLY GENERATED BY xml2cmake
PROJECT(OpenPMD_database)

INCLUDE(${VISIT_SOURCE_DIR}/CMake/PluginMacros.cmake)

ADD_DATABASE_CODE_GEN_TARGETS(OpenPMD)

SET(COMMON_SOURCES
OpenPMDPluginInfo.C
OpenPMDCommonPluginInfo.C
)

SET(LIBI_SOURCES
OpenPMDPluginInfo.C
)

SET(LIBM_SOURCES
OpenPMDMDServerPluginInfo.C
${COMMON_SOURCES}
OpenPMDClasses/PMDParticle.C
OpenPMDClasses/PMDField.C
OpenPMDClasses/PMDIteration.C
OpenPMDClasses/PMDFile.C
avtOpenPMDFileFormat.C
)

SET(LIBE_SOURCES
OpenPMDEnginePluginInfo.C
${COMMON_SOURCES}
OpenPMDClasses/PMDParticle.C
OpenPMDClasses/PMDField.C
OpenPMDClasses/PMDIteration.C
OpenPMDClasses/PMDFile.C
avtOpenPMDFileFormat.C
)

INCLUDE_DIRECTORIES(
${CMAKE_CURRENT_SOURCE_DIR}
${HDF5_INCLUDE_DIR}
${VISIT_COMMON_INCLUDES}
${VISIT_INCLUDE_DIR}/avt/DBAtts/MetaData
${VISIT_INCLUDE_DIR}/avt/DBAtts/SIL
${VISIT_INCLUDE_DIR}/avt/Database/Database
${VISIT_INCLUDE_DIR}/avt/Database/Formats
${VISIT_INCLUDE_DIR}/avt/Database/Ghost
${VISIT_INCLUDE_DIR}/avt/FileWriter
${VISIT_INCLUDE_DIR}/avt/Filters
${VISIT_INCLUDE_DIR}/avt/MIR/Base
${VISIT_INCLUDE_DIR}/avt/MIR/Tet
${VISIT_INCLUDE_DIR}/avt/MIR/Zoo
${VISIT_INCLUDE_DIR}/avt/Math
${VISIT_INCLUDE_DIR}/avt/Pipeline/AbstractFilters
${VISIT_INCLUDE_DIR}/avt/Pipeline/Data
${VISIT_INCLUDE_DIR}/avt/Pipeline/Pipeline
${VISIT_INCLUDE_DIR}/avt/Pipeline/Sinks
${VISIT_INCLUDE_DIR}/avt/Pipeline/Sources
${VISIT_INCLUDE_DIR}/avt/VisWindow/VisWindow
${VISIT_INCLUDE_DIR}/visit_vtk/full
${VISIT_INCLUDE_DIR}/visit_vtk/lightweight
${VTK_INCLUDE_DIRS}
)

LINK_DIRECTORIES(${VISIT_LIBRARY_DIR} ${HDF5_LIBRARY_DIR} )

ADD_LIBRARY(IOpenPMDDatabase ${LIBI_SOURCES})
TARGET_LINK_LIBRARIES(IOpenPMDDatabase visitcommon)
SET(INSTALLTARGETS IOpenPMDDatabase)

IF(NOT VISIT_ENGINE_ONLY AND NOT VISIT_DBIO_ONLY)
    ADD_LIBRARY(MOpenPMDDatabase ${LIBM_SOURCES})
    TARGET_LINK_LIBRARIES(MOpenPMDDatabase visitcommon avtdbatts avtdatabase_ser ${HDF5_LIB} )
    ADD_TARGET_DEFINITIONS(MOpenPMDDatabase MDSERVER)
    SET(INSTALLTARGETS ${INSTALLTARGETS} MOpenPMDDatabase)
ENDIF(NOT VISIT_ENGINE_ONLY AND NOT VISIT_DBIO_ONLY)

ADD_LIBRARY(EOpenPMDDatabase_ser ${LIBE_SOURCES})
TARGET_LINK_LIBRARIES(EOpenPMDDatabase_ser visitcommon avtdatabase_ser avtpipeline_ser ${HDF5_LIB} )
ADD_TARGET_DEFINITIONS(EOpenPMDDatabase_ser ENGINE)
SET(INSTALLTARGETS ${INSTALLTARGETS} EOpenPMDDatabase_ser)

IF(VISIT_PARALLEL)
    ADD_PARALLEL_LIBRARY(EOpenPMDDatabase_par ${LIBE_SOURCES})
    TARGET_LINK_LIBRARIES(EOpenPMDDatabase_par visitcommon avtdatabase_par avtpipeline_par ${HDF5_LIB} )
    ADD_TARGET_DEFINITIONS(EOpenPMDDatabase_par ENGINE)
    SET(INSTALLTARGETS ${INSTALLTARGETS} EOpenPMDDatabase_par)
ENDIF(VISIT_PARALLEL)

VISIT_INSTALL_DATABASE_PLUGINS(${INSTALLTARGETS})
VISIT_PLUGIN_TARGET_RTOD(databases ${INSTALLTARGETS})
VISIT_PLUGIN_TARGET_FOLDER(databases OpenPMD ${INSTALLTARGETS})

