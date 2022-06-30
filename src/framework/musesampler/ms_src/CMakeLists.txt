# SPDX-License-Identifier: GPL-3.0-only
# MuseScore-CLA-applies
#
# MuseScore
# Music Composition & Notation
#
# Copyright (C) 2022 MuseScore BVBA and others
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 3 as
# published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

include(GetPlatformInfo)

set(MODULE ms_src)

if (NOT MUSESAMPLER_SRC_PATH)
    message(FATAL_ERROR "MUSESAMPLER_SRC_PATH is not set")
endif()

option(USE_SPX_INSTRUMENTS "uses .spx intead of def.xml files" ON)
option(USE_XML_INSTRUMENT_MAP "If enabled, load from the InstrumentMap.xml (StaffPad style) rather than the .instruments database (written by the Muse app)" OFF)

if (BUILD_IS_DEBUG)
    set(MODULE_DEF -DDEVELOPMENT)
else()
    set(MODULE_DEF -DRELEASE)
endif()

set(MODULE_USE_UNITY_NONE ON)
set(THIRD_PARTY_DIR "${MUSESAMPLER_SRC_PATH}/../ThirdParty")

#########################################################################
file(MD5 ${MUSESAMPLER_SRC_PATH}/../../Assets/InstrumentLibrary/InstrumentMap.xml
    SP_INSTR_MAP_CHECKSUM)
configure_file(${MUSESAMPLER_SRC_PATH}/../StaffPad/Source/Instruments/InstrumentMapHash.cpp.in
    ${MUSESAMPLER_SRC_PATH}/../StaffPad/Source/Instruments/InstrumentMapHash.cpp)

if(APPLE)
    list(
        APPEND
        MSLIBRARIES
        PRIVATE
        ${THIRD_PARTY_DIR}/Opus/lib/osx/libogg.a
        ${THIRD_PARTY_DIR}/Opus/lib/osx/libopus.a
        ${THIRD_PARTY_DIR}/Opus/lib/osx/libopusfile.a
        ${THIRD_PARTY_DIR}/libopusenc/lib/osx/libopusenc-osx.a
        ${THIRD_PARTY_DIR}/OggVorbis/lib/osx/libogg.a
        ${THIRD_PARTY_DIR}/OggVorbis/lib/osx/libvorbis.a
        ${THIRD_PARTY_DIR}/OggVorbis/lib/osx/libvorbisfile.a
        ${THIRD_PARTY_DIR}/LAME/lib/osx/libmp3lame-3.99.5-osx-static.a
        ${THIRD_PARTY_DIR}/FLAC/lib/osx/libFLAC-1.3.2.a
        # Needed?
        "-framework AVFoundation"
        "-framework CoreML"
        "-framework AudioToolBox"
        "-framework Accelerate"
        "-framework AppKit"
        )
elseif(UNIX)
    list(
        APPEND
        MSLIBRARIES
        PRIVATE
        ${THIRD_PARTY_DIR}/Opus/lib/linux_x86_64/libopusfile.a
        ${THIRD_PARTY_DIR}/libopusenc/lib/linux_x86_64/libopusenc.a
        ${THIRD_PARTY_DIR}/FLAC/lib/linux_x86_64/libFLAC-static.a
        ${THIRD_PARTY_DIR}/OggVorbis/lib/linux_x86_64/libvorbisfile.a
        ${THIRD_PARTY_DIR}/LAME/lib/linux_x86_64/libmp3lame.a
        ${THIRD_PARTY_DIR}/Opus/lib/linux_x86_64/libopus.a
        ${THIRD_PARTY_DIR}/OggVorbis/lib/linux_x86_64/libvorbis.a
        ${THIRD_PARTY_DIR}/Opus/lib/linux_x86_64/libogg.a
        )
else()
    # until we have proper cmake way we just link the output files
    list(
        APPEND
        MSLIBRARIES
        ${library_output}/opusenc.lib
        ${library_output}/opus.lib
        ${library_output}/libogg_static.lib
        ${library_output}/opusfile.lib
        ${library_output}/libflac_static/libflac_static.lib
        ${library_output}/libvorbis_static.lib
        ${library_output}/libvorbisfile_static.lib
        ${THIRD_PARTY_DIR}/IPP/lib/intel64/ippcoremt.lib
        ${THIRD_PARTY_DIR}/IPP/lib/intel64/ippsmt.lib
        ${THIRD_PARTY_DIR}/IPP/lib/intel64/ippvmmt.lib
        ${THIRD_PARTY_DIR}/LAME/lib/win/x64/libmp3lame-static.lib
        ${THIRD_PARTY_DIR}/LAME/lib/win/x64/libmpghip-static.lib
        )
endif()


file(
    GLOB_RECURSE
    SOURCES
    CONFIGURE_DEPENDS
    ${MUSESAMPLER_SRC_PATH}/Source/*.h*
    ${MUSESAMPLER_SRC_PATH}/Source/*.c*
    ${MUSESAMPLER_SRC_PATH}/../PlaybackEventMap/*.h*
    ${MUSESAMPLER_SRC_PATH}/../PlaybackEventMap/*.c*
    ${MUSESAMPLER_SRC_PATH}/../StaffPad/Source/Instruments/InstrumentMapHash.cpp
    ${MUSESAMPLER_SRC_PATH}/../StaffPad/Source/Instruments/LoadedInstruments.cpp
    ${MUSESAMPLER_SRC_PATH}/../StaffPad/Source/PlaybackEngine/*.h*
    ${MUSESAMPLER_SRC_PATH}/../StaffPad/Source/PlaybackEngine/*.c*
    ${MUSESAMPLER_SRC_PATH}/../StaffPad/Source/Transposition/TranspositionHelpers.cpp
    ${MUSESAMPLER_SRC_PATH}/../StaffPad/Source/CrossPlatform/FileSystem/*.h*
    ${MUSESAMPLER_SRC_PATH}/../StaffPad/Source/CrossPlatform/FileSystem/*.c*
    ${MUSESAMPLER_SRC_PATH}/../StaffPad/Source/Model/AccidentalType.cpp
    ${MUSESAMPLER_SRC_PATH}/../StaffPad/Source/Utils/*.h*
    ${MUSESAMPLER_SRC_PATH}/../StaffPad/Source/Utils/*.c*
    ${MUSESAMPLER_SRC_PATH}/../StaffPad/Source/Instruments/InstrumentWrapperSpx.cpp
    ${MUSESAMPLER_SRC_PATH}/../StaffPad/Source/Instruments/DbInstrumentListProvider.cpp
    ${MUSESAMPLER_SRC_PATH}/../StaffPad/Source/Instruments/XmlInstrumentListProvider.cpp
    ${MUSESAMPLER_SRC_PATH}/../StaffPad/Source/File/Sql/SqliteDb.cpp
    ${MUSESAMPLER_SRC_PATH}/../StaffPad/Source/File/Sql/SqliteStmt.cpp

    ${THIRD_PARTY_DIR}/mbedtls/library/aes.c
    ${THIRD_PARTY_DIR}/mbedtls/library/aesni.c
    ${THIRD_PARTY_DIR}/mbedtls/library/entropy.c
    ${THIRD_PARTY_DIR}/mbedtls/library/entropy_poll.c
    ${THIRD_PARTY_DIR}/mbedtls/library/ctr_drbg.c
    ${THIRD_PARTY_DIR}/mbedtls/library/sha512.c
    ${THIRD_PARTY_DIR}/mbedtls/library/platform_util.c
    ${THIRD_PARTY_DIR}/mbedtls/library/timing.c
    ${THIRD_PARTY_DIR}/sqlite/sqlite3.c
    ${THIRD_PARTY_DIR}/XmlParser/pugixml.cpp)

if(APPLE OR UNIX)
    list(FILTER SOURCES EXCLUDE REGEX ".*Win32.cpp")
    list(FILTER SOURCES EXCLUDE REGEX "WASAPI.cpp")
    list(FILTER SOURCES EXCLUDE REGEX "MemoryMappedFileInputStream_Win32.cpp")
endif()

list(FILTER SOURCES EXCLUDE REGEX "AudioStaves")
list(FILTER SOURCES EXCLUDE REGEX "ValidatorPrototype.cpp")
list(FILTER SOURCES EXCLUDE REGEX "CubicBezier.cpp")
list(FILTER SOURCES EXCLUDE REGEX "Line.cpp")
list(FILTER SOURCES EXCLUDE REGEX "sp_log.cpp")
list(FILTER SOURCES EXCLUDE REGEX "DurationElementConstraint")
list(FILTER SOURCES EXCLUDE REGEX "BeatConstraint")
list(FILTER SOURCES EXCLUDE REGEX "StrokeRenderer.h")
list(FILTER SOURCES EXCLUDE REGEX "StrokeRenderer.cpp")
list(FILTER SOURCES EXCLUDE REGEX ".+\.cpp\.in")
list(FILTER SOURCES EXCLUDE REGEX "PlaybackEngine-stub-ios.cpp")

set(musesampler_include_dirs
    ${MUSESAMPLER_SRC_PATH}/Source
    ${MUSESAMPLER_SRC_PATH}/
    ${MUSESAMPLER_SRC_PATH}/../
    ${MUSESAMPLER_SRC_PATH}/../flip/include
    ${MUSESAMPLER_SRC_PATH}/../StaffPad/Source
    ${MUSESAMPLER_SRC_PATH}/../../UWP

    ${THIRD_PARTY_DIR}/mbedtls/include
    ${THIRD_PARTY_DIR}/OggVorbis/include
    ${THIRD_PARTY_DIR}/Logging/include
    ${THIRD_PARTY_DIR}/Logging/external/spdlog/include
    ${THIRD_PARTY_DIR}/Opus/include
    ${THIRD_PARTY_DIR}/libopusenc/include
    ${THIRD_PARTY_DIR}/readerwriterqueue
    ${THIRD_PARTY_DIR}/mbedtls/include)

list(APPEND COMPILE_DEFINES USE_MUSESAMPLER_SRC ON)
list(APPEND COMPILE_DEFINES UNICODE _UNICODE)
list(APPEND COMPILE_DEFINES MS_USE_INSTRUMENT_DB)

if(APPLE OR UNIX)
    list(APPEND COMPILE_OPTIONS -ffast-math)
    # ################### Objective-C Files #####################
    if(APPLE)
    else()
        list(APPEND COMPILE_DEFINES HAVE_MREMAP=0)
    endif()

else()
    list(APPEND COMPILE_OPTIONS /bigobj /await /fp:fast /MP)
endif()

set(MODULE_SRC
    ${MUSESAMPLER_SRC_PATH}
    ${SOURCES}
    )

set(MODULE_INCLUDE
    ${CMAKE_CURRENT_LIST_DIR}
    ${MUSESAMPLER_SRC_PATH}
    ${musesampler_include_dirs}
    )

set(MODULE_DEF
    ${COMPILE_DEFINES}
    )

set(MODULE_OVERRIDDEN_PCH
    ${MUSESAMPLER_SRC_PATH}/Source/pch.h
    )

set(MODULE_LINK
    ${MSLIBRARIES}
    )

include(${PROJECT_SOURCE_DIR}/build/module.cmake)

if(OS_IS_MAC)
    set_property(TARGET ${MODULE} APPEND_STRING PROPERTY COMPILE_FLAGS "-fobjc-arc" "-fobjc-link-runtime")

    set_target_properties(
        ${MODULE}
        PROPERTIES
        XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH[variant=Debug] "YES"
        FRAMEWORK TRUE
        FRAMEWORK_VERSION A
        XCODE_LINK_BUILD_PHASE_MODE KNOWN_LOCATION
        XCODE_ATTRIBUTE_LD_DYLIB_INSTALL_NAME
        "@rpath/ms_src.framework/ms_src"
        XCODE_ATTRIBUTE_ENABLE_BITCODE "NO"
        XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET 14.0
        )
endif()
