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

    /** \brief Returns the opacity of the desktop widget.
     *
     */
    int opacity() const;

    /** \brief Sets the opacity of the desktop widget.
     * \param[in] value opacity value [5-100].
     *
     */
    void setOpacity(int value);

    /** \brief Returns the volume of the video.
     *
     */
    int volume() const;

    /** \brief Sets the volume of the video.
     * \param[in] value volume value [0-100].
     *
     */
    void setVolume(int value);

    /** \brief Returns the size of the video (not real size but the ratio corresponding to the size * 100).
     *
     */
    int size() const;

    /** \brief Sets the size of the desktop widget.
     * \param[in] value size value in [25-200].
     *
     */
    void setSize(int value);

    /** \brief Returns the brightness of the video.
     *
     */
    int brightness() const;

    /** \brief Sets the brightness of the video.
     * \param[in] value brightness value [-100 - 100].
     *
     */
    void setBrightness(int value);

    /** \brief Returns the contrast of the video.
     *
     */
    int contrast() const;

    /** \brief Sets the contrast value of the video.
     * \param[in] value contrast value [-100 - 100].
     *
     */
    void setContrast(int value);

    /** \brief Returns the gamma of the video.
     *
     */
    int gamma() const;

    /** \brief Sets the gamma value of the video.
     * \param[in] value gamma value [-100 - 100].
     *
     */
    void setGamma(int value);

    /** \brief Returns the hue value of the video.
     *
     */
    int hue() const;

    /** \brief Sets the hue value of the video.
     * \param[in] value hue value [-100 - 100].
     *
     */
    void setHue(int value);

    /** \brief Returns the saturation value of the video.
     *
     */
    int saturation() const;

    /** \brief Sets the saturation value of the video.
     * \param[in] value saturation value [-100 - 100].
     *
     */
    void setSaturation(int value);

    /** \brief Returns true if subtitle loading is enabled.
     *
     */
    bool subtitlesEnabled() const;

    /** \brief Enables/disables video subtitles.
     * \param[in] enabled true to enable and false otherwise.
     *
     */
    void enableSubtitles(bool enabled);

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
