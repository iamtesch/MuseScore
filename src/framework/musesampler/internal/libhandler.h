/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-CLA-applies
 *
 * MuseScore
 * Music Composition & Notation
 *
 * Copyright (C) 2022 MuseScore BVBA and others
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef MU_MUSESAMPLER_LIBHANDLER_H
#define MU_MUSESAMPLER_LIBHANDLER_H

#include <memory>
#include <cstring>

#ifdef USE_MUSESAMPLER_SRC
#include "Api/musesampler_api.h"
#else
#include "apitypes.h"
#endif

namespace mu::musesampler {
#ifdef USE_MUSESAMPLER_SRC
struct MuseSamplerLibHandler
{
    ms_Result initLib() { return ms_init(); }
    ms_InstrumentList getInstrumentList() { return ms_get_instrument_list(); }
    ms_InstrumentInfo getNextInstrument(ms_InstrumentList instrument_list) { return ms_InstrumentList_get_next(instrument_list); }
    int getInstrumentId(ms_InstrumentInfo instrument) { return ms_Instrument_get_id(instrument); }
    const char* getInstrumentName(ms_InstrumentInfo instrument) { return ms_Instrument_get_name(instrument); }
    const char* getMusicXmlSoundId(ms_InstrumentInfo instrument) { return ms_Instrument_get_musicxml_sound(instrument); }
    const char* getMpeSoundId(ms_InstrumentInfo instrument) { return ms_Instrument_get_mpe_sound(instrument); }

    ms_PresetList getPresetList(ms_InstrumentInfo instrument_info) { return ms_Instrument_get_preset_list(instrument_info); }
    const char* getNextPreset(ms_PresetList preset_list) { return ms_PresetList_get_next(preset_list); }

    ms_MuseSampler create() { return ms_MuseSampler_create(); }
    void destroy(ms_MuseSampler sampler) { ms_MuseSampler_destroy(sampler); }
    ms_Result initSampler(ms_MuseSampler ms, double sample_rate, int block_size, int channel_count)
    {
        return ms_MuseSampler_init(ms, sample_rate, block_size, channel_count);
    }

    ms_Result clearScore(ms_MuseSampler ms) { return ms_MuseSampler_clear_score(ms); }
    ms_Track addTrack(ms_MuseSampler ms, int instrument_id) { return ms_MuseSampler_add_track(ms, instrument_id); }
    ms_Result finalizeTrack(ms_MuseSampler ms, ms_Track track) { return ms_MuseSampler_finalize_track(ms, track); }
    ms_Result clearTrack(ms_MuseSampler ms, ms_Track track) { return ms_MuseSampler_clear_track(ms, track); }

    ms_Result addDynamicsEvent(ms_MuseSampler ms, ms_Track track, ms_DynamicsEvent evt)
    {
        return ms_MuseSampler_add_track_dynamics_event(ms, track, evt);
    }
    ms_Result addNoteEvent(ms_MuseSampler ms, ms_Track track, ms_Event evt) { return ms_MuseSampler_add_track_note_event(ms, track, evt); }

    bool isRangedArticulation(ms_NoteArticulation art) { return ms_MuseSampler_is_ranged_articulation(art) == 1; }
    ms_Result addTrackEventRangeStart(ms_MuseSampler ms, ms_Track track, ms_NoteArticulation art)
    {
        return ms_MuseSampler_add_track_event_range_start(ms, track, art);
    }
    ms_Result addTrackEventRangeEnd(ms_MuseSampler ms, ms_Track track, ms_NoteArticulation art)
    {
        return ms_MuseSampler_add_track_event_range_end(ms, track, art);
    }

    void setPosition(ms_MuseSampler ms, long long micros) { return ms_MuseSampler_set_position(ms, micros); }
    void setPlaying(ms_MuseSampler ms, bool playing) { return ms_MuseSampler_set_playing(ms, playing ? 1 : 0); }
    ms_Result process(ms_MuseSampler ms, ms_OutputBuffer buff, long long micros) { return ms_MuseSampler_process(ms, buff, micros); }

    bool containsInstrument(const char* musicXmlSoundId)
    {
        auto instrumentList = getInstrumentList();
        if (instrumentList == nullptr) {
            return false;
        }

        while (auto instrument = getNextInstrument(instrumentList))
        {
            if (std::strcmp(getMusicXmlSoundId(instrument), musicXmlSoundId) == 0) {
                return true;
            }
        }

        return false;
    }

    MuseSamplerLibHandler(const char* /*path*/)
    {
        initLib();
    }

    bool isValid() const
    {
        return true;
    }
};
#else
struct MuseSamplerLibHandler
{
    ms_init initLib = nullptr;
    ms_get_instrument_list getInstrumentList = nullptr;
    ms_InstrumentList_get_next getNextInstrument = nullptr;
    ms_Instrument_get_id getInstrumentId = nullptr;
    ms_Instrument_get_name getInstrumentName = nullptr;
    ms_Instrument_get_musicxml_sound getMusicXmlSoundId = nullptr;
    ms_Instrument_get_mpe_sound getMpeSoundId = nullptr;

    ms_Instrument_get_preset_list getPresetList = nullptr;
    ms_PresetList_get_next getNextPreset = nullptr;

    ms_MuseSampler_create create = nullptr;
    ms_MuseSampler_destroy destroy = nullptr;
    ms_MuseSampler_init initSampler = nullptr;

    ms_MuseSampler_clear_score clearScore = nullptr;
    ms_MuseSampler_add_track addTrack = nullptr;
    ms_MuseSampler_finalize_track finalizeTrack = nullptr;
    ms_MuseSampler_clear_track clearTrack = nullptr;

    ms_MuseSampler_add_track_dynamics_event addDynamicsEvent = nullptr;
    ms_MuseSampler_add_track_note_event addNoteEvent = nullptr;
    ms_MuseSampler_is_ranged_articulation isRangedArticulation = nullptr;
    ms_MuseSampler_add_track_event_range_start addTrackEventRangeStart = nullptr;
    ms_MuseSampler_add_track_event_range_end addTrackEventRangeEnd = nullptr;

    ms_MuseSampler_set_position setPosition = nullptr;
    ms_MuseSampler_set_playing setPlaying = nullptr;
    ms_MuseSampler_process process = nullptr;

    bool containsInstrument(const char* musicXmlSoundId)
    {
        if (!isValid()) {
            LOGE() << "MuseSampler lib is not valid";

            printApiStatus();

            return false;
        }

        auto instrumentList = getInstrumentList();
        if (instrumentList == nullptr) {
            return false;
        }

        LOGD() << "Looking for available instruments";

        while (auto instrument = getNextInstrument(instrumentList))
        {
            LOGD() << "MusicXml ID: " << getMusicXmlSoundId(instrument);
            LOGD() << "MPE Sound ID: " << getMpeSoundId(instrument);

            if (std::strcmp(getMusicXmlSoundId(instrument), musicXmlSoundId) == 0) {
                LOGD() << "Found matching instrument, id: " << musicXmlSoundId;
                return true;
            }
        }

        LOGD() << "Unable to find any instrument sounds for ID: " << musicXmlSoundId;

        return false;
    }

    MuseSamplerLibHandler(const char* path)
    {
        m_lib = dlopen(path, RTLD_LAZY);

        if (!m_lib) {
            LOGE() << "Unable to open MuseSampler library, path: " << path;
            return;
        }

        initLib = (ms_init)dlsym(m_lib, "ms_init");
        getInstrumentList = (ms_get_instrument_list)dlsym(m_lib, "ms_get_instrument_list");
        getNextInstrument = (ms_InstrumentList_get_next)dlsym(m_lib, "ms_InstrumentList_get_next");
        getInstrumentId = (ms_Instrument_get_id)dlsym(m_lib, "ms_Instrument_get_id");
        getInstrumentName = (ms_Instrument_get_name)dlsym(m_lib, "ms_Instrument_get_name");
        getMusicXmlSoundId = (ms_Instrument_get_musicxml_sound)dlsym(m_lib, "ms_Instrument_get_musicxml_sound");
        getMpeSoundId = (ms_Instrument_get_mpe_sound)dlsym(m_lib, "ms_Instrument_get_mpe_sound");

        getPresetList = (ms_Instrument_get_preset_list)dlsym(m_lib, "ms_Instrument_get_preset_list");
        getNextPreset = (ms_PresetList_get_next)dlsym(m_lib, "ms_PresetList_get_next");

        create = (ms_MuseSampler_create)dlsym(m_lib, "ms_MuseSampler_create");
        destroy = (ms_MuseSampler_destroy)dlsym(m_lib, "ms_MuseSampler_destroy");
        initSampler = (ms_MuseSampler_init)dlsym(m_lib, "ms_MuseSampler_init");

        clearScore = (ms_MuseSampler_clear_score)dlsym(m_lib, "ms_MuseSampler_clear_score");
        addTrack = (ms_MuseSampler_add_track)dlsym(m_lib, "ms_MuseSampler_add_track");
        finalizeTrack = (ms_MuseSampler_finalize_track)dlsym(m_lib, "ms_MuseSampler_finalize_track");
        clearTrack = (ms_MuseSampler_clear_track)dlsym(m_lib, "ms_MuseSampler_clear_track");

        addDynamicsEvent = (ms_MuseSampler_add_track_dynamics_event)dlsym(m_lib, "ms_MuseSampler_add_track_dynamics_event");
        addNoteEvent = (ms_MuseSampler_add_track_note_event)dlsym(m_lib, "ms_MuseSampler_add_track_note_event");

        isRangedArticulation = (ms_MuseSampler_is_ranged_articulation)dlsym(m_lib, "ms_MuseSampler_is_ranged_articulation");
        addTrackEventRangeStart = (ms_MuseSampler_add_track_event_range_start)dlsym(m_lib, "ms_MuseSampler_add_track_event_range_start");
        addTrackEventRangeEnd = (ms_MuseSampler_add_track_event_range_end)dlsym(m_lib, "ms_MuseSampler_add_track_event_range_end");

        setPosition = (ms_MuseSampler_set_position)dlsym(m_lib, "ms_MuseSampler_set_position");
        setPlaying = (ms_MuseSampler_set_playing)dlsym(m_lib, "ms_MuseSampler_set_playing");
        process = (ms_MuseSampler_process)dlsym(m_lib, "ms_MuseSampler_process");

        initLib();
    }

    ~MuseSamplerLibHandler()
    {
        if (!m_lib) {
            return;
        }

        dlclose(m_lib);
    }

    bool isValid() const
    {
        return m_lib
               && initLib
               && getInstrumentList
               && getNextInstrument
               && getInstrumentId
               && getInstrumentName
               && getMusicXmlSoundId
               && getMpeSoundId
               && getPresetList
               && getNextPreset
               && create
               && destroy
               && initSampler
               && clearScore
               && addTrack
               && finalizeTrack
               && clearTrack
               && addDynamicsEvent
               && addNoteEvent
               && setPosition
               && setPlaying
               && isRangedArticulation
               && addTrackEventRangeStart
               && addTrackEventRangeEnd
               && process;
    }

private:
    void printApiStatus() const
    {
        LOGI() << "MuseSampler API status:"
               << "\n ms_get_instrument_list -" << reinterpret_cast<uint64_t>(getInstrumentList)
               << "\n ms_InstrumentList_get_next - " << reinterpret_cast<uint64_t>(getNextInstrument)
               << "\n ms_Instrument_get_id - " << reinterpret_cast<uint64_t>(getInstrumentId)
               << "\n ms_Instrument_get_name - " << reinterpret_cast<uint64_t>(getInstrumentName)
               << "\n ms_Instrument_get_musicxml_sound - " << reinterpret_cast<uint64_t>(getMusicXmlSoundId)
               << "\n ms_Instrument_get_mpe_sound - " << reinterpret_cast<uint64_t>(getMpeSoundId)
               << "\n ms_Instrument_get_preset_list - " << reinterpret_cast<uint64_t>(getPresetList)
               << "\n ms_PresetList_get_next - " << reinterpret_cast<uint64_t>(getNextPreset)
               << "\n ms_MuseSampler_create - " << reinterpret_cast<uint64_t>(create)
               << "\n ms_MuseSampler_destroy - " << reinterpret_cast<uint64_t>(destroy)
               << "\n ms_MuseSampler_init - " << reinterpret_cast<uint64_t>(initSampler)
               << "\n ms_MuseSampler_clear_score - " << reinterpret_cast<uint64_t>(clearScore)
               << "\n ms_MuseSampler_add_track - " << reinterpret_cast<uint64_t>(addTrack)
               << "\n ms_MuseSampler_finalize_track - " << reinterpret_cast<uint64_t>(finalizeTrack)
               << "\n ms_MuseSampler_add_track_dynamics_event - " << reinterpret_cast<uint64_t>(addDynamicsEvent)
               << "\n ms_MuseSampler_add_track_note_event - " << reinterpret_cast<uint64_t>(addNoteEvent)
               << "\n ms_MuseSampler_set_position - " << reinterpret_cast<uint64_t>(setPosition)
               << "\n ms_MuseSampler_set_playing - " << reinterpret_cast<uint64_t>(setPlaying)
               << "\n ms_MuseSampler_process - " << reinterpret_cast<uint64_t>(process);
    }

    MuseSamplerLib m_lib = nullptr;
};
#endif

using MuseSamplerLibHandlerPtr = std::shared_ptr<MuseSamplerLibHandler>;
}

#endif // MU_MUSESAMPLER_LIBHANDLER_H
