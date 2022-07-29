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

#include "musesamplerresolver.h"

#include "log.h"

#include "musesamplerwrapper.h"
#include "soundid_stringify.h"

using namespace mu;
using namespace mu::async;
using namespace mu::audio;
using namespace mu::audio::synth;
using namespace mu::musesampler;

MuseSamplerResolver::MuseSamplerResolver()
{
    io::path_t path = configuration()->libraryPath();

    m_libHandler = std::make_shared<MuseSamplerLibHandler>(path.c_str());
}

ISynthesizerPtr MuseSamplerResolver::resolveSynth(const audio::TrackId trackId, const audio::AudioInputParams& params) const
{
    return std::make_shared<MuseSamplerWrapper>(m_libHandler, params);
}

bool MuseSamplerResolver::hasCompatibleResources(const audio::PlaybackSetupData& setup) const
{
    if (!m_libHandler) {
        return false;
    }

    if (!setup.musicXmlSoundId.has_value()) {
        return false;
    }

    auto mpe_id = mpe::MpeIdToString(setup.id, setup.category, setup.subCategorySet);
    return m_libHandler->containsInstrument(mpe_id.c_str(), setup.musicXmlSoundId->c_str());
}

AudioResourceMetaList MuseSamplerResolver::resolveResources() const
{
    static AudioResourceMetaList result {
        {
            "Muse Sounds",
            AudioResourceType::MuseSamplerSoundPack,
            "Muse",
            /*hasNativeEditorSupport*/ false
        }
    };

    return result;
}

void MuseSamplerResolver::refresh()
{
    NOT_SUPPORTED;
}
