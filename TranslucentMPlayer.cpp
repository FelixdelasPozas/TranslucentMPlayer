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
#include "DesktopWidget.h"
#include "AboutDialog.h"
#include "PlayerManager.h"
#include "VideoConfigurationDialog.h"

// Qt
#include <QFileDialog>
#include <QSettings>
#include <QFileInfo>
#include <QMenu>
#include <QProcess>
#include <QMessageBox>

const QString TranslucentMPlayer::SETTINGS_FILENAME = "TranslucentMPlayer.ini";
const QString TranslucentMPlayer::KEY_MPLAYER_PATH  = "MPlayer executable path";
const QString TranslucentMPlayer::KEY_OPACITY       = "Opacity";
const QString TranslucentMPlayer::KEY_VOLUME        = "Volume";
const QString TranslucentMPlayer::KEY_POSITION      = "Position";
const QString TranslucentMPlayer::KEY_SIZE          = "Size";
const QString TranslucentMPlayer::KEY_LAST_DIR      = "Last used directory";

const QString FILES_FILTER_VIDEO = QObject::tr("Video files (*.avi *.vfw *.divx *.mpg *.mpeg *.m1v *.m2v *.mpv *.dv *.3gp *.mov *.mp4 *.m4v *.mqv *.dat *.vcd *.ogg *.ogm *.ogv *.ogx *.asf *.wmv *.bin *.iso *.vob *.mkv *.nsv *.ram *.flv *.rm *.swf *.ts *.rmvb *.drv-ms *.m2t *.m2ts *.mts *.rec *.wtv *.f4v *.hdmov *.webm *.vp8 *.bik *.smk *.m4b *.wtv)");
const QString FILES_FILTER_ALL   = QObject::tr("All files (*.*)");

//-----------------------------------------------------------------
TranslucentMPlayer::TranslucentMPlayer()
: m_manager{nullptr}
, m_icon   {QIcon(":TranslucentMPlayer/film.svg"), this}
{
  loadSettings();

  auto menu = new QMenu{};

  auto open   = new QAction{QIcon{":/TranslucentMPlayer/folder.svg"},      tr("Add files to playlist..."), menu};
  auto config = new QAction{QIcon{":/TranslucentMPlayer/config.svg"},      tr("Configure..."),             menu};
  auto video  = new QAction{QIcon{":/TranslucentMPlayer/videoconfig.svg"}, tr("Video Settings..."),        menu};
  auto about  = new QAction{QIcon{":/TranslucentMPlayer/film.svg"},        tr("About..."),                 menu};
  auto quit   = new QAction{QIcon{":/TranslucentMPlayer/exit.svg"},        tr("Quit"),                     menu};

  connect(open,   SIGNAL(triggered(bool)), this, SLOT(openMediaFile()));
  connect(config, SIGNAL(triggered(bool)), this, SLOT(onConfigTriggered()));
  connect(video,  SIGNAL(triggered(bool)), this, SLOT(onVideoSettingsTriggered()));
  connect(about,  SIGNAL(triggered(bool)), this, SLOT(onAboutTriggered()));
  connect(quit,   SIGNAL(triggered(bool)), this, SLOT(onExitTriggered()));

  m_playListMenu = new QMenu{"Playlist"};
  m_playListMenu->setIcon(QIcon{":/TranslucentMPlayer/list.svg"});

  menu->addAction(open);
  menu->addSeparator();
  menu->addMenu(m_playListMenu);
  menu->addSeparator();
  menu->addAction(config);
  menu->addAction(video);
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

  openMediaFile();

  if(m_playList.isEmpty())
  {
    return false;
  }

  return true;
}

//-----------------------------------------------------------------
void TranslucentMPlayer::openMediaFile()
{
  QStringList filters;
  filters << FILES_FILTER_VIDEO << FILES_FILTER_ALL;

  auto directory = QDir::current();
  if(!m_lastPath.isEmpty())
  {
    directory = QDir{m_lastPath};
    if(!directory.exists() && !directory.isRoot())
    {
      directory.cdUp();
    }

    if(directory.isRoot())
    {
      directory = QDir::current();
    }
  }

  QFileDialog openDialog;
  openDialog.setWindowIcon(QIcon(":/TranslucentMPlayer/film.svg"));
  openDialog.setWindowTitle(tr("Open media file"));
  openDialog.setDirectory(directory);
  openDialog.setOption(QFileDialog::DontUseNativeDialog, true);
  openDialog.setReadOnly(true);
  openDialog.setNameFilters(filters);
  openDialog.setLabelText(QFileDialog::Accept, tr("Open Video File(s)"));
  openDialog.setLabelText(QFileDialog::Reject, tr("Quit"));
  openDialog.setFileMode(QFileDialog::ExistingFiles);

  if((openDialog.exec() != QDialog::Accepted) || openDialog.selectedFiles().isEmpty())
  {
    return;
  }

  auto files = openDialog.selectedFiles();
  QStringList invalidFiles, validFiles;

  for(auto file: files)
  {
    if(m_playList.contains(file))
    {
      invalidFiles << file;
      continue;
    }

    m_playList << file;
    validFiles << file;

    auto info       = QFileInfo{file};
    auto fileAction = new QAction{info.baseName(), m_playListMenu};

    connect(fileAction, SIGNAL(triggered()), this, SLOT(onPlaylistItemTriggered()));

    m_lastPath = info.absolutePath();

    m_playListMenu->addAction(fileAction);
  }

  if(!invalidFiles.isEmpty())
  {
    QMessageBox dialog;
    dialog.setWindowIcon(QIcon(":/TranslucentMPlayer/film.svg"));
    dialog.setWindowTitle(tr("Files already in the playlist"));
    dialog.setIcon(QMessageBox::Information);

    auto message = tr("Can't add the following files, they're already in the playlist.\n\n");
    for (auto file : invalidFiles)
    {
      auto info = QFileInfo
      { file };
      message += "- " + info.baseName() + "\n";
    }

    dialog.setText(message);
    dialog.exec();
  }

  if(!validFiles.isEmpty())
  {
    if(!m_icon.isVisible())
    {
      m_icon.show();
    }

    if(!m_manager || !m_manager->isPlaying())
    {
      auto file = validFiles.first();
      int pos = m_playList.indexOf(file);

      m_playListMenu->actions().at(pos)->setIcon(QIcon(":/TranslucentMPlayer/play.svg"));

      play(file);
    }
  }
}

//-----------------------------------------------------------------
void TranslucentMPlayer::onPlaylistItemTriggered()
{
  auto action = qobject_cast<QAction *>(sender());

  auto menuActions = m_playListMenu->actions();

  int index = 0;
  for(int i = 0; i < menuActions.size(); ++i)
  {
    if(menuActions[i] == action)
    {
      action->setIcon(QIcon(":/TranslucentMPlayer/play.svg"));
      index = i;
    }
    else
    {
      if(!menuActions[i]->icon().isNull())
      {
        menuActions[i]->setIcon(QIcon());
      }
    }
  }

  play(m_playList.at(index));
}

//-----------------------------------------------------------------
void TranslucentMPlayer::onVideoSettingsTriggered()
{
  VideoConfigurationDialog dialog(m_manager);
  dialog.exec();
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
void TranslucentMPlayer::onManagerFinishedPlaying()
{
  int index = 0;
  auto actions = m_playListMenu->actions();
  for(auto action: actions)
  {
    if(!action->icon().isNull())
    {
      action->setIcon(QIcon());
      if(action != actions.last())
      {
        actions[++index]->setIcon(QIcon(":/TranslucentMPlayer/play.svg"));

        play(m_playList.at(index));
        return;
      }
    }
    ++index;
  }
}

//-----------------------------------------------------------------
void TranslucentMPlayer::play(const QString &fileName)
{
  if(!m_manager)
  {
    m_manager = new PlayerManager(m_playerPath);

    connect(m_manager, SIGNAL(finishedPlaying()),
            this,      SLOT(onManagerFinishedPlaying()));
  }

  m_manager->play(fileName);
}

//-----------------------------------------------------------------
void TranslucentMPlayer::loadSettings()
{
  QSettings settings{SETTINGS_FILENAME, QSettings::IniFormat};

  m_playerPath = settings.value(KEY_MPLAYER_PATH, QString()).toString();
  m_lastPath   = settings.value(KEY_LAST_DIR,     QString()).toString();
  m_opacity    = settings.value(KEY_OPACITY,      60).toInt();
  m_volume     = settings.value(KEY_VOLUME,       50).toInt();
  m_position   = settings.value(KEY_POSITION,     QPoint{0,0}).toPoint();
  m_size       = settings.value(KEY_SIZE,         1.0).toFloat();
}

//-----------------------------------------------------------------
void TranslucentMPlayer::saveSettings()
{
  QSettings settings{SETTINGS_FILENAME, QSettings::IniFormat};

  settings.setValue(KEY_MPLAYER_PATH, m_playerPath);
  settings.setValue(KEY_LAST_DIR,     m_lastPath);
  settings.setValue(KEY_OPACITY,      m_opacity);
  settings.setValue(KEY_VOLUME,       m_volume);
  settings.setValue(KEY_POSITION,     m_position);
  settings.setValue(KEY_SIZE,         m_position);
}
