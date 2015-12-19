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
, m_muted      {false}
{
}

//-----------------------------------------------------------------
void VolumeWidgetAction::setVolume(int value)
{
  if(!isMuted() && m_volume != value)
  {
    setWidgets(value);
    m_volume = value;
  }
}

//-----------------------------------------------------------------
void VolumeWidgetAction::reset()
{
  m_muted = false;

  blockSignals(true);
  for(auto widget: createdWidgets())
  {
    auto item = widget->layout()->itemAt(0);
    auto button = qobject_cast<QPushButton *>(item->widget());
    button->setChecked(false);
    if(m_volume != 0)
    {
      button->setIcon(QIcon(":/TranslucentMPlayer/speaker.svg"));
    }
    else
    {
      button->setIcon(QIcon(":/TranslucentMPlayer/mute.svg"));
    }

    item = widget->layout()->itemAt(1);
    auto slider = qobject_cast<QSlider *>(item->widget());
    slider->setValue(m_volume);
  }
  blockSignals(false);
}

//-----------------------------------------------------------------
bool VolumeWidgetAction::isMuted() const
{
  return m_muted;
}

//-----------------------------------------------------------------
int VolumeWidgetAction::volume() const
{
  return m_volume;
}

//-----------------------------------------------------------------
void VolumeWidgetAction::onButtonClicked(bool enabled)
{
  if(enabled)
  {
    if(m_volume != 0)
    {
      auto volume = m_volume;
      setWidgets(0);
      emit volumeChanged(0);
      m_volume = volume;
    }
  }
  else
  {
    if(m_volume != 0)
    {
      setWidgets(m_volume);
      emit volumeChanged(m_volume);
    }
  }

  m_muted = enabled;
}

//-----------------------------------------------------------------
void VolumeWidgetAction::onVolumeChanged(int value)
{
  if(m_volume != value)
  {
    m_volume = value;
    setWidgets(value);
    emit volumeChanged(value);
  }
}

//-----------------------------------------------------------------
QWidget* VolumeWidgetAction::createWidget(QWidget* parent)
{
  auto layout = new QHBoxLayout;
  layout->setSpacing(3);
  layout->setContentsMargins(3,3,3,3);
  layout->setMargin(3);

  auto button = new QPushButton();
  button->setCheckable(true);
  button->setFixedSize(QSize{24,24});
  button->setIcon(QIcon(":/TranslucentMPlayer/speaker.svg"));

  auto slider = new QSlider(Qt::Horizontal);
  slider->setMinimum(0);
  slider->setMaximum(100);
  slider->setValue(m_volume);
  slider->setFixedHeight(20);

  connect(button, SIGNAL(clicked(bool)),     this, SLOT(onButtonClicked(bool)));
  connect(slider, SIGNAL(valueChanged(int)), this, SLOT(onVolumeChanged(int)));

  layout->addWidget(button, 0);
  layout->addWidget(slider, 1);

  auto widget = new QWidget(parent);
  widget->setLayout(layout);

  return widget;
}

//-----------------------------------------------------------------
void VolumeWidgetAction::setWidgets(int value)
{
  blockSignals(true);
  for(auto widget: createdWidgets())
  {
    auto item = widget->layout()->itemAt(0);
    auto button = qobject_cast<QPushButton *>(item->widget());
    if(value == 0)
    {
      button->setIcon(QIcon(":/TranslucentMPlayer/mute.svg"));
    }
    else
    {
      button->setIcon(QIcon(":/TranslucentMPlayer/speaker.svg"));
    }

    item = widget->layout()->itemAt(1);
    auto slider = qobject_cast<QSlider *>(item->widget());
    slider->setValue(value);
  }
  blockSignals(false);
}
