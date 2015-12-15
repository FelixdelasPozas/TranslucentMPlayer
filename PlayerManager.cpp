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

// Qt
#include <QDir>
#include <QPoint>
#include <QDebug>

//-----------------------------------------------------------------
PlayerManager::PlayerManager(const QString &playerPath)
: m_playerPath      {playerPath}
, m_process         {this}
, m_desktopWidget   {false, nullptr}
, m_opacity         {60}
, m_volume          {100}
, m_size            {100}
, m_brightness      {0}
, m_contrast        {0}
, m_gamma           {0}
, m_hue             {0}
, m_saturation      {0}
, m_subtitlesEnabled{false}
, m_videoWidth      {0}
, m_videoHeight     {0}
{
  connect(&m_process, SIGNAL(readyReadStandardError()),
          this,      SLOT(onErrorAvailable()));
  connect(&m_process, SIGNAL(readyReadStandardOutput()),
          this,      SLOT(onOutputAvailable()));
}

//-----------------------------------------------------------------
PlayerManager::~PlayerManager()
{
  stop();
}

//-----------------------------------------------------------------
void PlayerManager::play(const QString& fileName)
{
  if(m_file == fileName && isPlaying()) return;

  m_file = fileName;

  if(isPlaying())
  {
    stop();
  }

  QStringList arguments;
  arguments << "-slave";
  arguments << "-vo";
  arguments << "gl";
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
  arguments << "-noautosub";
  arguments << "-subcp";
  arguments << "es:cp1145";
  arguments << fileName;

  m_process.start(m_playerPath, arguments);
}

//-----------------------------------------------------------------
void PlayerManager::stop()
{
  if(isPlaying())
  {
    m_process.write("stop\n");
    m_process.write("quit 0\n");
    m_process.waitForBytesWritten(-1);
    m_process.close();

    if(isPlaying())
    {
      m_process.kill();
    }
  }
}

//-----------------------------------------------------------------
void PlayerManager::onErrorAvailable()
{
  auto data = m_process.readAllStandardError();
  qDebug() << QString().fromLocal8Bit(data);
}

//-----------------------------------------------------------------
int PlayerManager::opacity() const
{
  return m_opacity;
}

//-----------------------------------------------------------------
void PlayerManager::setOpacity(int value)
{
  if(m_opacity != value)
  {
    m_opacity = value;

    m_desktopWidget.setOpacity(value);
  }
}

//-----------------------------------------------------------------
int PlayerManager::volume() const
{
  return m_volume;
}

//-----------------------------------------------------------------
void PlayerManager::setVolume(int value)
{
  if(m_volume != value)
  {
    m_volume = value;

    m_process.write(QString("volume %1 1\n").arg(value).toUtf8());
  }
}

//-----------------------------------------------------------------
int PlayerManager::size() const
{
  return m_size;
}

//-----------------------------------------------------------------
void PlayerManager::setSize(int value)
{
  if(m_size != value)
  {
    m_size = value;

    auto ratio = value/100.0;
    m_desktopWidget.setVideoSize(QSize{static_cast<int>(m_videoWidth*ratio), static_cast<int>(m_videoHeight*ratio)});
  }
}

//-----------------------------------------------------------------
int PlayerManager::brightness() const
{
  return m_brightness;
}

//-----------------------------------------------------------------
void PlayerManager::setBrightness(int value)
{
  if(m_brightness != value)
  {
    m_brightness = value;

    m_process.write(QString("brightness %1 1\n").arg(value).toUtf8());
  }
}

//-----------------------------------------------------------------
int PlayerManager::contrast() const
{
  return m_contrast;
}

//-----------------------------------------------------------------
void PlayerManager::setContrast(int value)
{
  if(m_contrast != value)
  {
    m_contrast = value;

    m_process.write(QString("contrast %1 1\n").arg(value).toUtf8());
  }
}

//-----------------------------------------------------------------
int PlayerManager::gamma() const
{
  return m_gamma;
}

//-----------------------------------------------------------------
void PlayerManager::setGamma(int value)
{
  if(m_gamma != value)
  {
    m_gamma = value;

    m_process.write(QString("gamma %1 1\n").arg(value).toUtf8());
  }
}

//-----------------------------------------------------------------
int PlayerManager::hue() const
{
  return m_hue;
}

//-----------------------------------------------------------------
void PlayerManager::setHue(int value)
{
  if(m_hue != value)
  {
    m_hue = value;

    m_process.write(QString("hue %1 1\n").arg(value).toUtf8());
  }
}

//-----------------------------------------------------------------
int PlayerManager::saturation() const
{
  return m_saturation;
}

//-----------------------------------------------------------------
void PlayerManager::setSaturation(int value)
{
  if(m_saturation != value)
  {
    m_saturation = value;

    m_process.write(QString("saturation %1 1\n").arg(value).toUtf8());
  }
}

//-----------------------------------------------------------------
bool PlayerManager::subtitlesEnabled() const
{
  return m_subtitlesEnabled;
}

//-----------------------------------------------------------------
void PlayerManager::enableSubtitles(bool value)
{
  if(m_subtitlesEnabled != value)
  {
    m_subtitlesEnabled = value;

    if(m_subtitlesEnabled)
    {
      auto info = QFileInfo{m_file};
      auto path = QDir{info.absolutePath()};

      QStringList filters;
      filters << "*.srt" << "*.sub" << "*.ssa" << "*.ass" << "*.idx" << "*.txt" << "*.smi" << "*.rt" << "*.utf" << "*.aqt";

      auto subtitleFiles = path.entryList(filters, QDir::Readable|QDir::Files);
      if(!subtitleFiles.isEmpty())
      {
        auto file = path.absoluteFilePath(subtitleFiles.first());

        m_process.write(QString("sub_load %1\n").arg(file).toUtf8());
      }

      // enables internal subtitles if embedded in video and there's no separated subtitle files.
      m_process.write("sub_select 0\n");
    }
    else
    {
      m_process.write("sub_remove\n");
      m_process.write("sub_select -1\n");
    }
  }
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
        m_videoWidth  = resolution[0].toInt();
        m_videoHeight = resolution[1].toInt();

        m_desktopWidget.hide();
        m_desktopWidget.setVideoSize(QSize{m_videoWidth, m_videoHeight});
        m_desktopWidget.show();
      }
    }
  }
}

//-----------------------------------------------------------------
bool PlayerManager::isPlaying() const
{
  return m_process.isOpen();
}

//-----------------------------------------------------------------
const QSize PlayerManager::videoSize() const
{
  auto ratio = m_size/100.0;

  return QSize{static_cast<int>(m_videoWidth*ratio), static_cast<int>(m_videoHeight*ratio)};
}

//-----------------------------------------------------------------
void PlayerManager::setWidgetPosition(const QPoint &point)
{
  m_desktopWidget.setPosition(point);
}

//-----------------------------------------------------------------
const QPoint PlayerManager::widgetPosition() const
{
  return m_desktopWidget.pos();
}
