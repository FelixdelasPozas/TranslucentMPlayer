/*
 File: AboutDialog.cpp
 Created on: 12/12/2015
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
#include <AboutDialog.h>

// Qt
#include <QtGlobal>
#include <QDateTime>
#include <QDesktopServices>
#include <QUrl>

const QString AboutDialog::VERSION = QString("version 1.4.1");

//-----------------------------------------------------------------
AboutDialog::AboutDialog(QWidget *parent, Qt::WindowFlags flags)
: QDialog(parent, flags)
{
  setupUi(this);

  setWindowFlags(windowFlags() & ~(Qt::WindowContextHelpButtonHint) & ~(Qt::WindowMaximizeButtonHint) & ~(Qt::WindowMinimizeButtonHint));

  auto compilation_date = QString(__DATE__);
  auto compilation_time = QString(" (") + QString(__TIME__) + QString(")");

  m_compilationDate->setText(tr("Compiled on ") + compilation_date + compilation_time);
  m_copy->setText(tr("Copyright (c) 2017-%1 Félix de las Pozas Álvarez").arg(QDateTime::currentDateTime().date().year()));
  m_version->setText(VERSION);

  m_qtVersion->setText(tr("version %1.%2.%3").arg(QT_VERSION_MAJOR).arg(QT_VERSION_MINOR).arg(QT_VERSION_PATCH));

  QObject::connect(m_kofiLabel, &ClickableHoverLabel::clicked,
                  [this](){ QDesktopServices::openUrl(QUrl{"https://ko-fi.com/felixdelaspozas"}); });    
}
