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
    const QString m_playerPath;    /** mplayer executable absolute path. */
    QProcess      m_process;       /** mplayer process.                  */
    DesktopWidget m_desktopWidget; /** desktop widget for video display. */
};

#endif // PLAYERMANAGER_H_
