/*
 File: DesktopWidget.cpp
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

// project
#include "DesktopWidget.h"

// Qt
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

//-----------------------------------------------------------------
DesktopWidget::DesktopWidget(bool dragEnable, QWidget *parent)
: QWidget      {parent, Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint|Qt::NoDropShadowWindowHint|Qt::WindowTransparentForInput|Qt::Tool}
{
  setAttribute(Qt::WA_AlwaysStackOnTop);
  setAttribute(Qt::WA_NoSystemBackground);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  setGeometry(QRect(0,0, 100, 100));
  setWindowOpacity(0.60);

  move(0,0);
}

//-----------------------------------------------------------------
void DesktopWidget::setPosition(const QPoint& position)
{
  if(position != pos())
  {
    move(position);
  }
}

//-----------------------------------------------------------------
void DesktopWidget::setOpacity(const int opacity)
{
  if(opacity != windowOpacity())
  {
    setWindowOpacity(opacity/100.0);

    if(isVisible()) repaint();
  }
}

//-----------------------------------------------------------------
void DesktopWidget::setVideoSize(const QSize& widgetSize)
{
  if(widgetSize != size())
  {
    setGeometry(QRect(0,0, widgetSize.width(), widgetSize.height()));
  }
}
