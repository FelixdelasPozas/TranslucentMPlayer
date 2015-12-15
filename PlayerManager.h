/*
 File: PlayerManager.h
 Created on: 13/12/2015
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

#ifndef PLAYERMANAGER_H_
#define PLAYERMANAGER_H_

// Project
#include "DesktopWidget.h"

// Qt
#include <QProcess>
#include <QSize>
#include <QObject>

/** \class PlayerManager
 * \brief QProcress around mplayer wrapper.
 *
 */
class PlayerManager
: public QObject
{
    Q_OBJECT
  public:
    /** \brief PlayerManager class constructor.
     * \param[in] playerPath mplayer executable absolute path.
     *
     */
    explicit PlayerManager(const QString &playerPath);

    /** \brief PlayerManager class virtual destructor.
     *
     */
    virtual ~PlayerManager();

    /** \brief Starts playing the given filename and shows the widget.
     * \param[in] fileName media file absolute path.
     *
     */
    void play(const QString &fileName);

    /** \brief Returns true if there is a video currently playing.
     *
     */
    bool isPlaying() const;

    /** \brief Stops the current play.
     *
     */
    void stop();

    /** \brief
     *
     */
    int opacity() const;

    /** \brief
     *
     */
    void setOpacity(int value);

    /** \brief
     *
     */
    int volume() const;

    /** \brief
     *
     */
    void setVolume(int value);

    /** \brief
     *
     */
    int size() const;

    /** \brief
     *
     */
    void setSize(int value);

    /** \brief
     *
     */
    int brightness() const;

    /** \brief
     *
     */
    void setBrightness(int value);

    /** \brief
     *
     */
    int contrast() const;

    /** \brief
     *
     */
    void setContrast(int value);

    /** \brief
     *
     */
    int gamma() const;

    /** \brief
     *
     */
    void setGamma(int value);

    /** \brief
     *
     */
    int hue() const;

    /** \brief
     *
     */
    void setHue(int value);

    /** \brief
     *
     */
    int saturation() const;

    /** \brief
     *
     */
    void setSaturation(int value);

    /** \brief
     *
     */
    bool subtitlesEnabled() const;

    /** \brief
     *
     */
    void enableSubtitles(bool value);

    /** \brief Returns the size of the video.
     *
     */
    const QSize videoSize() const;

    /** \brief Sets the widget position to the given screen coordinate.
     * \param[in] point top-left corner position of the desktop widget.
     *
     */
    void setWidgetPosition(const QPoint &point);

    /** \brief Returns the position of the desktop widget.
     *
     */
    const QPoint widgetPosition() const;

  private slots:
    /** \brief Manages mplayer errors.
     *
     */
    void onErrorAvailable();

    /** \brief Manages mplayer output.
     *
     */
    void onOutputAvailable();

  private:
    const QString m_playerPath;    /** mplayer executable absolute path.                    */
    QProcess      m_process;       /** mplayer process.                                     */
    DesktopWidget m_desktopWidget; /** desktop widget for video display.                    */
    QString       m_file;          /** currently playing file or empty if stopped.          */

    int m_opacity;                 /** video opacity value [0-100]                          */
    int m_volume;                  /** video volume value [0-100]                           */
    int m_size;                    /** video size multiplier [25 - 200] = value/100         */
    int m_brightness;              /** video brightness value [-100 - 100]                  */
    int m_contrast;                /** video contrast value [-100 - 100]                    */
    int m_gamma;                   /** video gamma value [-100 - 100]                       */
    int m_hue;                     /** video hue value [-100 - 100]                         */
    int m_saturation;              /** video saturation value [-100 - 100]                  */
    bool m_subtitlesEnabled;       /** true if subtitles must be loaded and shown (if any). */

    int m_videoWidth;              /** detected video width.                                */
    int m_videoHeight;             /** detected video height.                               */
};

#endif // PLAYERMANAGER_H_
