/*
 File: TranslucentMPlayer.cpp
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

// Project
#include "TranslucentMPlayer.h"
#include "ConfigurationDialog.h"
#include "AboutDialog.h"

// Qt
#include <QFileDialog>
#include <QSettings>
#include <QFileInfo>
#include <QMenu>
#include <QDebug>

const QString TranslucentMPlayer::SETTINGS_FILENAME = "TranslucentMPlayer.ini";
const QString TranslucentMPlayer::KEY_MPLAYER_PATH  = "MPlayer executable path";
const QString TranslucentMPlayer::KEY_OPACITY       = "Opacity";
const QString TranslucentMPlayer::KEY_VOLUME        = "Volume";
const QString TranslucentMPlayer::KEY_POSITION      = "Position";

//-----------------------------------------------------------------
TranslucentMPlayer::TranslucentMPlayer()
: m_icon {QIcon(":TranslucentMPlayer/film.svg"), this}
{
  loadSettings();

  auto menu = new QMenu{};

  auto config = new QAction{QIcon{":TranslucentMPlayer/config.svg"}, tr("Configure..."), menu};
  auto about  = new QAction{QIcon{":TranslucentMPlayer/film.svg"},   tr("About..."),     menu};
  auto quit   = new QAction{QIcon{":TranslucentMPlayer/exit.svg"},   tr("Quit"),         menu};

  connect(config, SIGNAL(triggered(bool)), this, SLOT(onConfigTriggered()));
  connect(about,  SIGNAL(triggered(bool)), this, SLOT(onAboutTriggered()));
  connect(quit,   SIGNAL(triggered(bool)), this, SLOT(onExitTriggered()));

  menu->addAction(config);
  menu->addSeparator();
  menu->addAction(about);
  menu->addAction(quit);

  m_icon.setContextMenu(menu);
}

//-----------------------------------------------------------------
TranslucentMPlayer::~TranslucentMPlayer()
{
  saveSettings();
}

//-----------------------------------------------------------------
bool TranslucentMPlayer::start()
{
  auto mplayerFile = QFileInfo{m_playerPath};

  if(!mplayerFile.isExecutable() || !mplayerFile.isReadable())
  {
    onConfigTriggered();
  }

  QFileDialog openDialog;
  openDialog.setWindowIcon(QIcon(":/TranslucentMPlayer/film.svg"));
  openDialog.setWindowTitle(tr("Open media file"));
  openDialog.setDirectory(QDir::currentPath());
  openDialog.setOption(QFileDialog::DontUseNativeDialog, true);
  openDialog.setReadOnly(true);
  openDialog.setLabelText(QFileDialog::Accept, tr("Open Video"));
  openDialog.setLabelText(QFileDialog::Reject, tr("Quit"));
  openDialog.setFileMode(QFileDialog::ExistingFile);

  auto fileName = QFileDialog::getOpenFileNames(nullptr, tr("Open media file"), QDir::currentPath(), tr("Media files (*.*)"), nullptr, QFileDialog::ReadOnly);

  if(fileName.isEmpty())
  {
    return false;
  }

  m_icon.show();
  return true;
}

//-----------------------------------------------------------------
void TranslucentMPlayer::onAboutTriggered()
{
  AboutDialog about;
  about.exec();
}

//-----------------------------------------------------------------
void TranslucentMPlayer::onExitTriggered()
{
  m_icon.hide();

  emit finished();
}

//-----------------------------------------------------------------
void TranslucentMPlayer::onConfigTriggered()
{
  ConfigurationDialog conf;
  conf.setMplayerPath(m_playerPath);

  if(conf.exec() == QDialog::Accepted)
  {
    m_playerPath = conf.mplayerPath();
  }
}

//-----------------------------------------------------------------
void TranslucentMPlayer::loadSettings()
{
  QSettings settings{SETTINGS_FILENAME, QSettings::IniFormat};

  m_playerPath = settings.value(KEY_MPLAYER_PATH, QString()).toString();
  m_opacity    = settings.value(KEY_OPACITY, 60).toInt();
  m_volume     = settings.value(KEY_VOLUME, 50).toInt();
  m_position   = settings.value(KEY_POSITION, QPoint{0,0}).toPoint();
}

//-----------------------------------------------------------------
void TranslucentMPlayer::saveSettings()
{
  QSettings settings{SETTINGS_FILENAME, QSettings::IniFormat};

  settings.setValue(KEY_MPLAYER_PATH, m_playerPath);
  settings.setValue(KEY_OPACITY, m_opacity);
  settings.setValue(KEY_VOLUME, m_volume);
  settings.setValue(KEY_POSITION, m_position);
}
