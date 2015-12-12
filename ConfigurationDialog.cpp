/*
 File: ConfigurationDialog.cpp
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

// Qt
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>

//-----------------------------------------------------------------
ConfigurationDialog::ConfigurationDialog(QWidget *parent, Qt::WindowFlags flags)
: QDialog{parent, flags}
{
  setupUi(this);

  connect(m_pathButton, SIGNAL(clicked()),
          this,         SLOT(onDirButtonPressed()));
}

//-----------------------------------------------------------------
const QString ConfigurationDialog::mplayerPath() const
{
  return m_playerPath->text();
}

//-----------------------------------------------------------------
void ConfigurationDialog::setMplayerPath(const QString &path)
{
  auto filePath = path;
  filePath = filePath.replace('/', QDir::separator());

  m_playerPath->setText(filePath);
  m_versionText->setText(mplayerVersion());
}

//-----------------------------------------------------------------
const QString ConfigurationDialog::mplayerVersion()
{
  if(!m_playerPath->text().isEmpty())
  {
    QStringList parameters;
    parameters << "-v";

    QProcess process(this);
    process.start(m_playerPath->text(), parameters, QProcess::ReadOnly);
    process.waitForFinished();
    auto output = process.readLine();
    process.close();

    auto versionString = QString().fromStdString(output.toStdString());
    auto parts = versionString.split(" ", QString::SkipEmptyParts);

    if(!parts.isEmpty() && parts.first().compare("MPlayer") == 0)
    {
      return parts[1];
    }
  }

  return QString("MPlayer not detected.");
}

//-----------------------------------------------------------------
void ConfigurationDialog::accept()
{
  if(!m_playerPath->text().isEmpty())
  {
    QFileInfo info{m_playerPath->text()};

    if(!info.exists() || !info.isExecutable())
    {
      QMessageBox::warning(this, tr("Invalid executable"), tr("The specified file doesn't exist or is not an executable"));
      return;
    }
  }

  if(m_versionText->text().compare("MPlayer not detected.") == 0)
  {
    QMessageBox::warning(this, tr("Invalid executable"), tr("Unable to identify the executable as a valid MPlayer executable. Unable to get the version string."));
    return;
  }

  QDialog::accept();
}

//-----------------------------------------------------------------
void ConfigurationDialog::closeEvent(QCloseEvent* e)
{
  if(result() != QDialog::Rejected)
  {
    if(!m_playerPath->text().isEmpty())
    {
      QFileInfo info{m_playerPath->text()};

      if(!info.exists() || !info.isExecutable())
      {
        QMessageBox::warning(this, tr("Invalid executable"), tr("The specified file doesn't exist or is not an executable"));
        return;
      }
    }

    if(m_versionText->text().compare("MPlayer not detected.") == 0)
    {
      QMessageBox::warning(this, tr("Invalid executable"), tr("Unable to identify the executable as a valid MPlayer executable. Unable to get the version string."));
      return;
    }
  }

  QDialog::closeEvent(e);
}

//-----------------------------------------------------------------
void ConfigurationDialog::onDirButtonPressed()
{
  QString currentPath = (m_playerPath->text().isEmpty() ? QDir::currentPath() : QFileInfo{m_playerPath->text()}.absolutePath());

  auto fileName = QFileDialog::getOpenFileName(this, tr("Open MPlayer executable"), currentPath, tr("Executable files (*.exe)"));

  if(!fileName.isEmpty())
  {
    QFileInfo info{fileName};

    if(!info.exists() || !info.isExecutable())
    {
      QMessageBox::warning(this, tr("Invalid executable"), tr("The specified file doesn't exist or is not an executable"));
      return;
    }

    setMplayerPath(info.absoluteFilePath());

    if(m_versionText->text().compare("MPlayer not detected.") == 0)
    {
      QMessageBox::warning(this, tr("Invalid executable"), tr("Unable to identify the executable as a valid MPlayer executable. Unable to get the version string."));
      return;
    }
  }
}
