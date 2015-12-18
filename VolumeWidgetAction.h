/*
 File: VolumeWidgetAction.h
 Created on: 17/12/2015
 Author: Felix de las Pozas Alvarez

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef VOLUMEWIDGETACTION_H_
#define VOLUMEWIDGETACTION_H_

// Qt
#include <QWidgetAction>

/** \class VolumeWidgetAction
 * \brief Volume widget for the tray icon.
 *
 */
class VolumeWidgetAction
: public QWidgetAction
{
    Q_OBJECT
  public:
    /** \brief VolumeWidgetAction class constructor.
     * \param[in] startValue volume value.
     * \param[in] parent raw pointer of the QObject parent of this one.
     *
     */
    explicit VolumeWidgetAction(int startValue = 100, QObject *parent = nullptr);

    /** \brief VolumeWidgetAction class virtual destructor.
     *
     */
    virtual ~VolumeWidgetAction()
    {}

    /** \brief Sets the slider value, if 0 checks the mute button.
     *
     */
    void setVolume(int value);

  signals:
    void volumeChanged(int value);

  protected:
    virtual QWidget *createWidget(QWidget *parent) override final;

  private:
    int m_volume; /** starting value for volume slider .*/
};

#endif // VOLUMEWIDGETACTION_H_
