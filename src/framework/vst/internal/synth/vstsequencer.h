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

#ifndef MU_VST_VSTSEQUENCER_H
#define MU_VST_VSTSEQUENCER_H

#include "audio/abstracteventsequencer.h"

#include "vsttypes.h"

namespace mu::vst {
class VstSequencer : public audio::AbstractEventSequencer<VstEvent, PluginParamInfo>
{
public:
    void updateOffStreamEvents(const mpe::PlaybackEventsMap& changes) override;
    void updateMainStreamEvents(const mpe::PlaybackEventsMap& changes) override;
    void updateDynamicChanges(const mpe::DynamicLevelMap& changes) override;

private:
    void updatePlaybackEvents(EventSequenceMap& destination, const mpe::PlaybackEventsMap& changes);

    VstEvent buildEvent(const Steinberg::Vst::Event::EventTypes type, const int32_t noteIdx, const float velocityFraction);

    int32_t noteIndex(const mpe::pitch_level_t pitchLevel) const;
    float noteVelocityFraction(const mpe::NoteEvent& noteEvent) const;
    float expressionLevel(const mpe::dynamic_level_t dynamicLevel) const;
};
}

#endif // MU_VST_VSTSEQUENCER_H
