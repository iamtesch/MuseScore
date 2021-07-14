/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-CLA-applies
 *
 * MuseScore
 * Music Composition & Notation
 *
 * Copyright (C) 2021 MuseScore BVBA and others
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

import QtQuick 2.15
import QtQuick.Controls 2.15

import MuseScore.UiComponents 1.0

Slider {
    id: root

    height: 140
    width: 12

    from: -48
    to: 12
    value: 0
    stepSize: 0.1
    orientation: Qt.Vertical

    background: Rectangle {
        implicitWidth: 2
        implicitHeight: 140
        width: 2
        height: 140
        color: Utils.colorWithAlpha(ui.theme.fontPrimaryColor, 0.5)
    }

    handle: Rectangle {
        x: 0
        y: (1 - root.position) * (root.availableHeight - height)
        implicitWidth: 16
        implicitHeight: 33
        radius: 2
        color: ui.theme.fontPrimaryColor
        border.color: "#00000075"

        Rectangle {
            anchors {
                verticalCenter: parent.verticalCenter
                left: parent.left
                right: parent.right
                leftMargin: 2
                rightMargin: 2
            }

            height: 1
            radius: height/2
            color: "#000000"
        }
    }
}
