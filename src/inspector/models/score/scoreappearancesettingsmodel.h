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
#ifndef MU_INSPECTOR_SCOREAPPEARANCESETTINGSMODEL_H
#define MU_INSPECTOR_SCOREAPPEARANCESETTINGSMODEL_H

#include "models/abstractinspectormodel.h"

#include "internal/pagetypelistmodel.h"

namespace mu::inspector {
class ScoreAppearanceSettingsModel : public AbstractInspectorModel
{
    Q_OBJECT

    Q_PROPERTY(PageTypeListModel * pageTypeListModel READ pageTypeListModel CONSTANT)
    Q_PROPERTY(int orientationType READ orientationType WRITE setOrientationType NOTIFY orientationTypeChanged)
    Q_PROPERTY(qreal staffSpacing READ staffSpacing WRITE setStaffSpacing NOTIFY staffSpacingChanged)
    Q_PROPERTY(qreal staffDistance READ staffDistance WRITE setStaffDistance NOTIFY staffDistanceChanged)

public:
    explicit ScoreAppearanceSettingsModel(QObject* parent, IElementRepositoryService* repository);

    Q_INVOKABLE void showPageSettings();
    Q_INVOKABLE void showStyleSettings();

    void createProperties() override;
    void requestElements() override;
    void loadProperties() override;
    void resetProperties() override;

    bool hasAcceptableElements() const override;

    PageTypeListModel* pageTypeListModel() const;

    int orientationType() const;
    qreal staffSpacing() const;
    qreal staffDistance() const;

public slots:
    void setPageTypeListModel(PageTypeListModel* pageTypeListModel);
    void setOrientationType(int orientationType);
    void setStaffSpacing(qreal staffSpacing);
    void setStaffDistance(qreal staffDistance);

signals:
    void orientationTypeChanged(int orientationType);
    void staffSpacingChanged(qreal staffSpacing);
    void staffDistanceChanged(qreal staffDistance);

private:
    void updatePageSize();

    int m_currentPageSizeId = -1;
    int m_orientationType = 0;
    qreal m_staffSpacing = 0.0;
    qreal m_staffDistance = 0.0;

    PageTypeListModel* m_pageTypeListModel = nullptr;
};
}

#endif // MU_INSPECTOR_SCOREAPPEARANCESETTINGSMODEL_H
