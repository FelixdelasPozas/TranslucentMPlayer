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
, m_dragEnable {dragEnable}
, m_buttonDown {false}
{
  setAttribute(Qt::WA_AlwaysStackOnTop);
  setAttribute(Qt::WA_NoSystemBackground);

  enableDrag(dragEnable);

  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  auto desktopRect = QApplication::desktop()->geometry();
  m_limitX = desktopRect.width()-100;
  m_limitY = desktopRect.height()-100;

  setGeometry(QRect(0,0, 100, 100));
  setWindowOpacity(0.60);

  move(0,0);
}

//-----------------------------------------------------------------
void DesktopWidget::mousePressEvent(QMouseEvent* e)
{
  if(m_dragEnable && underMouse() && e->button() == Qt::MouseButton::LeftButton)
  {
    m_point = e->globalPos();

    m_buttonDown = true;
    emit beingDragged();
  }
  else
  {
    QWidget::mousePressEvent(e);
  }
}

//-----------------------------------------------------------------
void DesktopWidget::mouseReleaseEvent(QMouseEvent* e)
{
  if(m_dragEnable && underMouse() && e->button() == Qt::MouseButton::LeftButton)
  {
    m_point -= e->globalPos();
    setPosition(pos()-m_point);
    m_point = e->globalPos();

    m_buttonDown = false;
  }
  else
  {
    QWidget::mousePressEvent(e);
  }
}

//-----------------------------------------------------------------
void DesktopWidget::mouseMoveEvent(QMouseEvent* e)
{
  if(m_dragEnable && m_buttonDown)
  {
    m_point -= e->globalPos();
    setPosition(pos()-m_point);
    m_point = e->globalPos();
  }
  else
  {
    QWidget::mousePressEvent(e);
  }
}

//-----------------------------------------------------------------
void DesktopWidget::setPosition(const QPoint& position)
{
  if(position != pos())
  {
    auto newPosition = position;
    if(newPosition.x() < 0) newPosition.setX(0);
    if(newPosition.y() < 0) newPosition.setY(0);

    if(newPosition.x() > m_limitX) newPosition.setX(m_limitX);
    if(newPosition.y() > m_limitY) newPosition.setY(m_limitY);

    move(newPosition);
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
void DesktopWidget::setVideoSize(const QSize& size)
{
  auto desktopRect = QApplication::desktop()->geometry();
  m_limitX = desktopRect.width()-size.width();
  m_limitY = desktopRect.height()-size.height();

  setGeometry(QRect(0,0, size.width(), size.height()));
  // TODO: set position again?
}

//-----------------------------------------------------------------
void DesktopWidget::enableDrag(bool value)
{
  if(value)
  {
    setWindowFlags(windowFlags() & ~Qt::WindowTransparentForInput);
  }
  else
  {
    setWindowFlags(windowFlags() | Qt::WindowTransparentForInput);
  }
}

//-----------------------------------------------------------------
void DesktopWidget::paintEvent(QPaintEvent *e)
{
  if(m_dragEnable)
  {
    QBrush brush(Qt::white, Qt::SolidPattern);
    auto windowRect = rect();

    QPainter painter;
    painter.begin(this);
    painter.setBrush(brush);
    brush.setStyle(Qt::SolidPattern);
    painter.setPen(Qt::white);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setCompositionMode(QPainter::CompositionMode_Difference);

    painter.drawRect(windowRect);
    painter.drawLine(QPoint{static_cast<int>(windowRect.width()*0.25), static_cast<int>(windowRect.height()*0.5)},
                     QPoint{static_cast<int>(windowRect.width()*0.75), static_cast<int>(windowRect.height()*0.5)});
    painter.drawLine(QPoint{static_cast<int>(windowRect.width()*0.5), static_cast<int>(windowRect.height()*0.25)},
                     QPoint{static_cast<int>(windowRect.width()*0.5), static_cast<int>(windowRect.height()*0.75)});

    painter.end();
  }
  else
  {
    QWidget::paintEvent(e);
  }
}
