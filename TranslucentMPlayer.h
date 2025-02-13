/*
 File: TranslucentMPlayer.h
 Created on: 11/12/2015
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

#ifndef TRANSLUCENTMPLAYER_H_
#define TRANSLUCENTMPLAYER_H_

// Qt
#include <QString>
#include <QPoint>
#include <QSystemTrayIcon>
#include <QWaitCondition>
#include <QMutex>
#include <QObject>

class QProcess;
class QSettings;
class PlayerManager;
class ProgressWidgetAction;
class VolumeWidgetAction;

/** \class TranslucentMPlayer
 * \brief Main application.
 *
 */
class TranslucentMPlayer
: public QObject
{
    Q_OBJECT
  public:
    /** \brief TranslucentMPlayer class constructor.
     *
     */
    explicit TranslucentMPlayer(QObject *parent = nullptr);

    /** \brief TranslucentMPlayer class virtual destructor.
     *
     */
    virtual ~TranslucentMPlayer();

    /** \brief Ask for configuration if needed and starts the video play and widgets.
     *         Returns true on a successful start and false otherwise.
     *
     */
    bool start();

  signals:
    void finished();

  private slots:
    /** \brief Shows the about dialog.
     *
     */
    void onAboutTriggered();

    /** \brief Exits the application.
     *
     */
    void onExitTriggered();

    /** \brief Shows the configuration dialog.
     *
     */
    void onConfigTriggered();

    /** \brief Opens a dialog for selecting media files and adds them to the playlist. If
     *         there isn't a video playing, starts the next one on the playlist.
     *
     */
    void openMediaFile();

    /** \brief Stops playing the current video (if any) and starts playing the selected one.
     *
     */
    void onPlaylistItemTriggered();

    /** \brief Shows the video settings dialog.
     *
     */
    void onVideoSettingsTriggered();

    /** \brief Plays the next file in the playlist, if any, when the process signals that mplayer has finished.
     *
     */
    void onManagerFinishedPlaying();

    /** \brief Starts a previously paused video.
     *
     */
    void onWidgetPlay();

    /** \brief Pauses a playing video.
     *
     */
    void onWidgetPause();

    /** \brief Changes the time of the video.
     * \param[in] value time value in seconds of the new position.
     *
     *
     */
    void onProgressChanged(int value);

    /** \brief Changes the volume of the playing video.
     * \param[in] value volume value in [0-100].
     *
     */
    void onVolumeChanged(int value);

    /** \brief Updates the progress and the volume of the tray menu.
     *
     */
    void onMenuShow();

    /** \brief Signals the player to stop time signals.
     *
     */
    void onMenuHide();

    /** \brief Clears the playlist and ask for new files.
     *
     */
    void onClearPlaylistTriggered();

    /** \brief Shows the video in a monitor in fullscreen mode with full opacity.
     *
     */
    void onFullscreenTriggered();

  private:
    /** \brief Plays the given file.
     * \param[in] fileName file absolute file path.
     *
     */
    void play(const QString &fileName);

    /** \brief Loads settings from ini file.
     *
     */
    void loadSettings();

    /** \brief Saves settings to ini file.
     *
     */
    void saveSettings();

    /** \brief Helper method to uncheck all fullscreen menu actions.
     *
     */
    void uncheckFullscreenActions();

    /** \brief Returns the application settings depending on the presence of the INI file.
     *
     */
    std::unique_ptr<QSettings> applicationSettings() const;

    static const QString SETTINGS_FILENAME;
    static const QString KEY_MPLAYER_PATH;
    static const QString KEY_OPACITY;
    static const QString KEY_VOLUME;
    static const QString KEY_SIZE;
    static const QString KEY_LAST_DIR;
    static const QString KEY_VIDEO_BRIGHTNESS;
    static const QString KEY_VIDEO_CONTRAST;
    static const QString KEY_VIDEO_GAMMA;
    static const QString KEY_VIDEO_HUE;
    static const QString KEY_VIDEO_SATURATION;
    static const QString KEY_VIDEO_POSITION;
    static const QString KEY_SHOW_SUBTITLES;

    QString         m_playerPath;       /** absolute path of the mplayer executable.         */
    QString         m_lastPath;         /** last used directory.                             */
    int             m_volume;           /** volume level in [0-100].                         */
    int             m_opacity;          /** opacity level in [0-100].                        */
    QString         m_position;         /** video position on dektop.                        */
    int             m_size;             /** video size in [0.25-2]                           */
    int             m_brightness;       /** video brightness in [-100 - 100]                 */
    int             m_contrast;         /** video contrast int [-100 - 100]                  */
    int             m_gamma;            /** video gamma in [-100 - 100]                      */
    int             m_hue;              /** video hue in [-100 - 100]                        */
    int             m_saturation;       /** video saturation in [-100 - 100]                 */
    bool            m_subtitlesEnabled; /** true to show subtitles and false otherwise.      */
    QStringList     m_playList;         /** list of media files to play secuentially.        */
    PlayerManager  *m_manager;          /** player manager.                                  */
    QSystemTrayIcon m_icon;             /** application tray icon.                           */
    QMenu          *m_playListMenu;     /** playlist menu in tray icon.                      */
    QMenu          *m_fullscreenMenu;   /** fullscreen monitors list.                        */
    bool            m_paused;           /** true if the video is paused and false otherwise. */

    ProgressWidgetAction *m_progressWidget; /** menu progress widget to set the progress and play/pause from tray. */
    VolumeWidgetAction   *m_volumeWidget;   /** menu volume widget for volume modification from tray.              */
};

#endif // TRANSLUCENTMPLAYER_H_
