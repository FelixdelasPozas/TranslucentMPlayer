/*
 File: PlayerManager.cpp
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

// Project
#include "PlayerManager.h"
#include "DesktopWidget.h"

//-----------------------------------------------------------------
PlayerManager::PlayerManager(const QString &playerPath)
: m_playerPath   {playerPath}
, m_process      {this}
, m_desktopWidget{false, nullptr}
{
  connect(&m_process, SIGNAL(readyReadStandardError()),
          this,      SLOT(onErrorAvailable()));
  connect(&m_process, SIGNAL(readyReadStandardOutput()),
          this,      SLOT(onOutputAvailable()));
}

//-----------------------------------------------------------------
PlayerManager::~PlayerManager()
{
  if(m_process.isOpen())
  {
    m_process.write("quit\n");
    m_process.waitForFinished(-1);
    m_process.close();
  }
}

//-----------------------------------------------------------------
void PlayerManager::play(const QString& fileName)
{
  QStringList arguments;
  arguments << "-slave";
  arguments << "-vo";
  arguments << "direct3d";
  arguments << "-ao";
  arguments << "win32";
  arguments << "-cache";
  arguments << "8192";
  arguments << "-idle";
  arguments << "-wid";
  arguments << QString().number(static_cast<int>(m_desktopWidget.winId()));
  arguments << "-framedrop";
  arguments << "-nomouseinput";
  arguments << "-nokeepaspect";
  arguments << "-monitorpixelaspect";
  arguments << "1";
  arguments << "-noborder";
  arguments << fileName;

  m_process.start(m_playerPath, arguments);
}

//-----------------------------------------------------------------
void PlayerManager::onErrorAvailable()
{
  auto data = m_process.readAllStandardError();
  // TODO: manage error
}

//-----------------------------------------------------------------
void PlayerManager::onOutputAvailable()
{
  while(true)
  {
    auto data = m_process.readLine();
    if(data.size() == 0)
    {
      break;
    }

    auto dataString = QString().fromUtf8(data);
    auto parts = dataString.split(' ', QString::SkipEmptyParts);
    if(!parts.isEmpty() && ((parts[0].compare("VO:") == 0) || (parts[0].compare("VIDEO:") == 0)))
    {
      auto resolution = parts[2].split('x');
      if(!resolution.isEmpty())
      {
        m_desktopWidget.hide();
        m_desktopWidget.setVideoSize(QSize{resolution[0].toInt(), resolution[1].toInt()});
        m_desktopWidget.show();
      }
    }
  }
}

