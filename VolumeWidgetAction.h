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

    /** \brief Resets the state of the volume mute button.
     *
     */
    void reset();

    /** \brief Returns true if muted and false otherwise.
     *
     */
    bool isMuted() const;

    /** \brief Returns the volume value.
     *
     */
    int volume() const;

  signals:
    void volumeChanged(int value);

  private slots:
    /** \brief Modifies the volume, muting if the parameter is true and restoring it to the previous value otherwise.
     *
     */
    void onButtonClicked(bool state);

    /** \brief Emits the signal and stores the value.
     * \param[in] value volume value in [0-100].
     *
     */
    void onVolumeChanged(int value);

  protected:
    virtual QWidget *createWidget(QWidget *parent) override final;

  private:
    /** \brief Adjusts the widgets value to the given volume value.
     * \param[in] value volume value in [0-100]
     */
    void setWidgets(int value);

    int  m_volume; /** starting value for volume slider . */
    bool m_muted;  /** true if muted and false otherwise. */
};

#endif // VOLUMEWIDGETACTION_H_
