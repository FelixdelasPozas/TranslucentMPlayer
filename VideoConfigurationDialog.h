/*
 File: VideoConfigurationDialog.h
 Created on: 14/12/2015
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

#ifndef VIDEOCONFIGURATIONDIALOG_H_
#define VIDEOCONFIGURATIONDIALOG_H_

// Qt
#include <QDialog>
#include "ui_VideoConfigurationDialog.h"

class PlayerManager;

/** \class VideoConfigurationDialog
 * \brief Dialog for video position and properties configuration.
 *
 */
class VideoConfigurationDialog
: public QDialog
, private Ui_VideoConfigurationDialog
{
    Q_OBJECT
  public:
    /** \brief VideoConfigurationDialog class constructor.
     * \param[in] manager video manager.
     * \param[in] parent raw pointer of the QWidget parent of this one.
     * \param[in] flags window flags.
     *
     */
    explicit VideoConfigurationDialog(PlayerManager *manager, QWidget *parent = nullptr, Qt::WindowFlags flags = 0);

    /** \brief VideoConfigurationDialog class virtual destructor.
     *
     */
    virtual ~VideoConfigurationDialog()
    {}

  private slots:
    /** \brief Updates the UI and the video with the new opacity value.
     * \param[in] value opacity value in [5-100].
     *
     */
    void onOpacityValueChanged(int value);

    /** \brief Updates the UI and the video with the new size value.
     * \param[in] value size value in [25-200].
     *
     */
    void onSizeValueChanged(int value);

    /** \brief Updates the UI and the sound with the new volume value.
     * \param[in] value volume value in [0-100].
     *
     */
    void onVolumeValueChanged(int value);

    /** \brief Updates the UI and the video with the new brightness value.
     * \param[in] value brightness value in [-100 - +100].
     *
     */
    void onBrightnessValueChanged(int value);

    /** \brief Updates the UI and the video with the new contrast value.
     * \param[in] value contrast value in [-100 - +100].
     *
     */
    void onContrastValueChanged(int value);

    /** \brief Updates the UI and the video with the new gamma value.
     * \param[in] value gamma value in [-100 - +100].
     *
     */
    void onGammaValueChanged(int value);

    /** \brief Updates the UI and the video with the new hue value.
     * \param[in] value hue value in [-100 - +100].
     *
     */
    void onHueValueChanged(int value);

    /** \brief Updates the UI and the video with the new saturation value.
     * \param[in] value saturation value in [-100 - +100].
     *
     */
    void onSaturationValueChanged(int value);

    /** \brief Calls the manager to load and show video subtitles or to hide and unload.
     * \param[in] state checkbox state.
     *
     */
    void onSubtitlesStateChanged(int state);

    /** \brief Updates the position of the video.
     * \param[in] index new position combo box index.
     *
     */
    void onPositionChanged(int index);

  private:
    /** \brief Helper method to connect UI components signals.
     *
     */
    void connectSignals();

    PlayerManager *m_manager; /** video manager. */
};

#endif // VIDEOCONFIGURATIONDIALOG_H_
