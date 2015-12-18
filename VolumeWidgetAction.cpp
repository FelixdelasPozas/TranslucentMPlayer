/*
 File: VolumeWidgetAction.cpp
 Created on: 17/12/2015
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
#include "VolumeWidgetAction.h"

// Qt
#include <QPushButton>
#include <QSlider>
#include <QHBoxLayout>
#include <QLabel>
#include <QObject>

//-----------------------------------------------------------------
VolumeWidgetAction::VolumeWidgetAction(int startValue, QObject* parent)
: QWidgetAction{parent}
, m_volume     {startValue}
{
}

//-----------------------------------------------------------------
void VolumeWidgetAction::setVolume(int value)
{
  if(m_volume != value)
  {
    blockSignals(true);
    for(auto widget: createdWidgets())
    {
      auto item = widget->layout()->itemAt(1);
      auto slider = qobject_cast<QSlider *>(item->widget());
      slider->setValue(value);
    }
    blockSignals(false);

    m_volume = value;
  }
}

//-----------------------------------------------------------------
QWidget* VolumeWidgetAction::createWidget(QWidget* parent)
{
  auto layout = new QHBoxLayout;
  layout->setSpacing(3);
  layout->setContentsMargins(3,3,3,3);
  layout->setMargin(3);

  auto label = new QLabel();
  label->setFixedSize(QSize{20,20});
  label->setPixmap(QIcon(":/TranslucentMPlayer/speaker.svg").pixmap(QSize{18,18}));

  auto slider = new QSlider(Qt::Horizontal);
  slider->setMinimum(0);
  slider->setMaximum(100);
  slider->setValue(m_volume);
  slider->setFixedHeight(20);

  connect(slider, SIGNAL(valueChanged(int)), this, SIGNAL(volumeChanged(int)));

  layout->addWidget(label, 0);
  layout->addWidget(slider, 1);

  auto widget = new QWidget(parent);
  widget->setLayout(layout);

  return widget;
}
