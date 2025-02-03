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
#include <DesktopWidget.h>

// Qt
#include <QProcess>
#include <QSize>
#include <QObject>
#include <QTimer>

// C++
#include <cmath>
#include <functional>

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

    /** \brief Sets the absolute path to the mplayer executable. Doesn't check it's validity.
     *
     */
    void setMPlayerPath(const QString &path);

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
     * \param[in] positionName position name.
     *
     */
    void setWidgetPosition(const QString &positionName);

    /** \brief Returns the string of the position of the desktop widget in the positions list.
     *
     */
    const QString widgetPosition() const;

    /** \brief Returns the list of names of the preset positions.
     *
     */
    QStringList widgetPositionNames() const;

    /** \brief Enables/disables the signaling of video time procession.
     * \param[in] enabled true to signal the timing and false otherwise.
     *
     */
    void enableTiming(bool enabled);

    /** \brief Returns the video duration in seconds.
     *
     */
    int videoDuration() const;

    /** \brief Pauses the current video.
     *
     */
    void pause();

    /** \brief Resumes playing the current video.
     *
     */
    void unpause();

    /** \brief Returns the filename of media being played or an empty string if stopped.
     *
     */
    QString filename() const;

    /** \brief Seeks the video to the given position in seconds.
     *
     */
    void setVideoTime(int seconds);

    /** \brief Displays the video with full opacity in the given screen. If the
     * screen pointer is null it returns to the non full-screen position and size.
     * \param[in] screen QScreen raw pointer.
     *
     */
    void setFullScreen(const QScreen *screen);

  signals:
    void finishedPlaying();
    void startedPlaying();
    void time(int seconds);

  private slots:
    /** \brief Manages mplayer errors.
     *
     */
    void onErrorAvailable();

    /** \brief Manages mplayer output.
     *
     */
    void onOutputAvailable();

    /** \brief Ask mplayer for current video time.
     *
     */
    void askTime();

  private:
    /** \brief Updates the properties of the video display.
     *
     */
    void setVideoProperties();

    /** \brief Computes the names of the preset positions based on desktop configuration.
     *
     */
    void computePositionsNames();

    /** \brief Computes the available positions based on desktop configuration.
     *
     */
    void computePositions();

    /** \brief Computes all the fixed positions and position names for the given QRect.
     * \param[in] rect QRect rectangle.
     *
     */
    void computeRectPositions(const QRect &rect);

    /** \brief Helper method to load the subtitles in mplayer.
     *
     */
    void loadSubtitles();

    /** \brief Helper method to unload the subtitles file (if any) and deactivate subtitles.
     *
     */
    void unloadSubtitles();

    /** \brief Helper method that returns a video size according to given ratio.
     * \param[in] ratio Double ratio value.
     *
     */
    inline QSize computeSize(const double ratio,
                             std::function<double(double)> func = [](double x){ return std::nearbyint(x); } ) const
    {
      return QSize{static_cast<int>(func(m_videoWidth*ratio)),
                   static_cast<int>(func(m_videoHeight*ratio))};
    }

  private:
    static const QStringList SUBTITLES_EXTENSIONS; /** subtitle files extensions. */

    QString       m_playerPath;              /** mplayer executable absolute path.                    */
    QProcess      m_process;                 /** mplayer process.                                     */
    DesktopWidget m_desktopWidget;           /** desktop widget for video display.                    */
    QString       m_file;                    /** currently playing file or empty if stopped.          */

    int m_opacity;                           /** video opacity value [0-100]                          */
    int m_volume;                            /** video volume value [0-100]                           */
    int m_size;                              /** video size multiplier [25 - 200] = value/100         */
    int m_brightness;                        /** video brightness value [-100 - 100]                  */
    int m_contrast;                          /** video contrast value [-100 - 100]                    */
    int m_gamma;                             /** video gamma value [-100 - 100]                       */
    int m_hue;                               /** video hue value [-100 - 100]                         */
    int m_saturation;                        /** video saturation value [-100 - 100]                  */
    QString m_widgetPosition;                /** widget position string.                              */
    bool m_subtitlesEnabled;                 /** true if subtitles must be loaded and shown (if any). */

    int m_videoWidth;                        /** detected video width.                                */
    int m_videoHeight;                       /** detected video height.                               */

    static const QStringList POSITION_NAMES; /** list of available preset positions.                  */
    QList<QPoint> m_widgetPositions;         /** list of computed preset widget positions.            */
    QStringList   m_widgetPositionNames;     /** list of names for computed preset positions.         */

    QTimer m_timer;                          /** timer for progress signaling.                        */
    int    m_duration;                       /** duration of the video in seconds.                    */
    bool   m_paused;                         /** true if the video is paused and false otherwise.     */
};

#endif // PLAYERMANAGER_H_
