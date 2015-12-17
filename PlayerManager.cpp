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
#include <QApplication>
#include <QDesktopWidget>

const QStringList PlayerManager::POSITION_NAMES = { QString("Top Left"),
                                                    QString("Top Center"),
                                                    QString("Top Right"),
                                                    QString("Center Left"),
                                                    QString("Center"),
                                                    QString("Center Right"),
                                                    QString("Bottom Left"),
                                                    QString("Bottom Center"),
                                                    QString("Bottom Right") };

const QStringList PlayerManager::SUBTITLES_EXTENSIONS = { "*.srt", "*.sub", "*.ssa", "*.ass", "*.idx", "*.txt", "*.smi", "*.rt", "*.utf", "*.aqt"};

//-----------------------------------------------------------------
PlayerManager::PlayerManager(const QString &playerPath)
: m_playerPath      {playerPath}
, m_process         {this}
, m_desktopWidget   {nullptr}
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
, m_duration        {0}
{
  connect(&m_process, SIGNAL(readyReadStandardError()),
          this,       SLOT(onErrorAvailable()));
  connect(&m_process, SIGNAL(readyReadStandardOutput()),
          this,       SLOT(onOutputAvailable()));

  m_timer.setSingleShot(false);
  m_timer.setInterval(1000);
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

  m_file.clear();

  if(isPlaying())
  {
    stop();
  }

  m_file = fileName;

  QStringList arguments;
  arguments << "-slave";
  arguments << "-vo";
  arguments << "gl";
  arguments << "-ao";
  arguments << "win32";
  arguments << "-cache";
  arguments << "8192";
  arguments << "-idle";
  arguments << "-msglevel";
  arguments << "statusline=6:global=6";
  arguments << "-osdlevel";
  arguments << "0";
  arguments << "-wid";
  arguments << QString().number(static_cast<int>(m_desktopWidget.winId()));
  arguments << "-framedrop";
  arguments << "-nomouseinput";
  arguments << "-nokeepaspect";
  arguments << "-monitorpixelaspect";
  arguments << "1";
  arguments << "-noborder";
  arguments << "-noautosub";
  arguments << "-utf8";
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

    m_duration = 0;
  }
}

//-----------------------------------------------------------------
void PlayerManager::setMPlayerPath(const QString &path)
{
  m_playerPath = path;
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

    if(isPlaying())
    {
      m_process.write(QString("volume %1 1\n").arg(value).toUtf8());
    }
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

    computePositions();

    if(!m_widgetPositionNames.isEmpty())
    {
      auto position = widgetPosition();
      auto point = m_widgetPositions.at(m_widgetPositionNames.indexOf(position));
      m_desktopWidget.setPosition(point);
    }
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

    if(isPlaying())
    {
      m_process.write(QString("brightness %1 1\n").arg(value).toUtf8());
    }
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

    if(isPlaying())
    {
      m_process.write(QString("contrast %1 1\n").arg(value).toUtf8());
    }
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

    if(isPlaying())
    {
      m_process.write(QString("gamma %1 1\n").arg(value).toUtf8());
    }
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

    if(isPlaying())
    {
      m_process.write(QString("hue %1 1\n").arg(value).toUtf8());
    }
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

    if(isPlaying())
    {
      m_process.write(QString("saturation %1 1\n").arg(value).toUtf8());
    }
  }
}

//-----------------------------------------------------------------
bool PlayerManager::subtitlesEnabled() const
{
  return m_subtitlesEnabled;
}

//-----------------------------------------------------------------
void PlayerManager::enableSubtitles(bool enabled)
{
  if(m_subtitlesEnabled != enabled)
  {
    m_subtitlesEnabled = enabled;

    if(isPlaying())
    {
      if(m_subtitlesEnabled)
      {
        loadSubtitles();
      }
      else
      {
        unloadSubtitles();
      }
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
    if(dataString.startsWith("EOF code:"))
    {
      m_desktopWidget.hide();
      emit finishedPlaying();
      return;
    }

    if(dataString.startsWith("ANS_LENGTH"))
    {
      dataString.remove(dataString.length()-4,4);
      auto parts = dataString.split("=");

      if(parts.size() == 2)
      {
        m_duration = parts[1].toInt();
      }

      return;
    }

    if(m_timer.isActive() && dataString.startsWith("ANS_TIME_POSITION"))
    {
      dataString.remove(dataString.length()-4,4);
      auto parts = dataString.split("=");

      if(parts.size() == 2)
      {
        emit time(parts[1].toFloat());
      }

      return;
    }

    auto parts = dataString.split(' ', QString::SkipEmptyParts);
    if(!parts.isEmpty() && (parts[0].compare("VO:") == 0))
    {
      auto resolution = parts[2].split('x');
      if(!resolution.isEmpty())
      {
        if(m_videoWidth == resolution[0].toInt() && m_videoHeight == resolution[1].toInt()) return;

        if(m_widgetPositionNames.isEmpty())
        {
          computePositionsNames();
        }

        m_videoWidth  = resolution[0].toInt();
        m_videoHeight = resolution[1].toInt();

        computePositions();

        auto ratio = m_size/100.0;
        m_desktopWidget.setVideoSize(QSize{static_cast<int>(m_videoWidth*ratio), static_cast<int>(m_videoHeight*ratio)});

        auto widgetPos = m_widgetPosition.isEmpty() ? 0 : m_widgetPositionNames.indexOf(m_widgetPosition);
        m_desktopWidget.setPosition(m_widgetPositions.at(widgetPos));

        m_process.write("get_time_length\n");
        m_process.waitForBytesWritten();

        setVideoProperties();

        m_process.write("osd 1\n");

        m_desktopWidget.show();

        emit startedPlaying();
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
void PlayerManager::setWidgetPosition(const QString &positionName)
{
  if(m_widgetPosition != positionName)
  {
    m_widgetPosition = positionName;

    if(!m_widgetPositionNames.isEmpty() && m_widgetPositionNames.contains(positionName))
    {
      auto position = m_widgetPositions.at(m_widgetPositionNames.indexOf(positionName));
      m_desktopWidget.setPosition(position);
    }
    else
    {
      m_desktopWidget.setPosition(QPoint{0,0});
    }
  }
}

//-----------------------------------------------------------------
const QString PlayerManager::widgetPosition() const
{
  auto name = m_widgetPositionNames.isEmpty() ? QString() : m_widgetPosition;
  return name;
}

//-----------------------------------------------------------------
QStringList PlayerManager::widgetPositionNames() const
{
  return m_widgetPositionNames;
}

//-----------------------------------------------------------------
void PlayerManager::enableTiming(bool enabled)
{
  if(enabled && !m_timer.isActive())
  {
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(askTime()));

    m_timer.start();
    return;
  }

  if(!enabled && m_timer.isActive())
  {
    disconnect(&m_timer, SIGNAL(timeout()), this, SLOT(askTime()));

    m_timer.stop();
  }
}

//-----------------------------------------------------------------
int PlayerManager::videoDuration() const
{
  return m_duration;
}

//-----------------------------------------------------------------
void PlayerManager::setVideoProperties()
{
  m_process.write(QString("volume %1 1\n").arg(m_volume).toUtf8());
  m_process.write(QString("brightness %1 1\n").arg(m_brightness).toUtf8());
  m_process.write(QString("contrast %1 1\n").arg(m_contrast).toUtf8());
  m_process.write(QString("gamma %1 1\n").arg(m_gamma).toUtf8());
  m_process.write(QString("hue %1 1\n").arg(m_hue).toUtf8());
  m_process.write(QString("saturation %1 1\n").arg(m_saturation).toUtf8());

  if(m_subtitlesEnabled)
  {
    loadSubtitles();
  }
}

//-----------------------------------------------------------------
void PlayerManager::computePositionsNames()
{
  for(auto position: POSITION_NAMES)
  {
    m_widgetPositionNames << QString("Global ") + position;
  }

  auto desktop = QApplication::desktop();
  for (int i = 0; i < desktop->numScreens(); ++i)
  {
    for(auto position: POSITION_NAMES)
    {
      m_widgetPositionNames << QString("Monitor %1 ").arg(i) + position;
    }
  }
}

//-----------------------------------------------------------------
void PlayerManager::computePositions()
{
  m_widgetPositions.clear();

  auto desktop = QApplication::desktop();
  computeRectPositions(desktop->geometry());

  for (int i = 0; i < desktop->numScreens(); ++i)
  {
    computeRectPositions(desktop->screenGeometry(i));
  }
}

//-----------------------------------------------------------------
void PlayerManager::computeRectPositions(const QRect& rect)
{
  auto widgetSize = videoSize();

  for(int y: {rect.y(), rect.y()+(rect.height()-widgetSize.height())/2, rect.y()+rect.height()-widgetSize.height()})
  {
    for(int x: {rect.x(), rect.x()+(rect.width()-widgetSize.width())/2, rect.x()+rect.width()-widgetSize.width()})
    {
      m_widgetPositions << QPoint{x,y};
    }
  }
}

//-----------------------------------------------------------------
void PlayerManager::loadSubtitles()
{
  auto info = QFileInfo{m_file};
  auto path = QDir{info.absolutePath()};

  QStringList filters;
  for(auto ext: SUBTITLES_EXTENSIONS)
  {
    filters << QString("%1%2").arg(info.baseName()).arg(ext);
  }

  auto subtitleFiles = path.entryList(filters, QDir::Readable|QDir::Files);
  if(!subtitleFiles.isEmpty())
  {
    auto file = path.absoluteFilePath(subtitleFiles.first());

    m_process.write(QString("sub_load \"%1\"\n").arg(file).toUtf8());
  }

  // enables internal subtitles if embedded in video and there's no separated subtitle files.
  m_process.write("sub_select 0\n");
}

//-----------------------------------------------------------------
void PlayerManager::unloadSubtitles()
{
  m_process.write("sub_remove\n");
  m_process.write("sub_select -1\n");
}

//-----------------------------------------------------------------
void PlayerManager::askTime()
{
  m_process.write("get_time_pos\n");
}
