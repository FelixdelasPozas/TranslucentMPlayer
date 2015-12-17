/*
 File: ProjectWidgetAction.cpp
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
#include "ProgressWidgetAction.h"

// Qt
#include <QObject>
#include <QSlider>
#include <QPushButton>
#include <QHBoxLayout>

//-----------------------------------------------------------------
ProgressWidgetAction::ProgressWidgetAction(int maxValue, int currentValue, QObject* parent)
: QWidgetAction{parent}
, m_maxValue   {maxValue}
, m_current    {currentValue}
{
}

//-----------------------------------------------------------------
void ProgressWidgetAction::setProgress(int value)
{
  if(m_current != value)
  {
    for(auto widget: createdWidgets())
    {
      auto item = widget->layout()->itemAt(1);
      auto slider = qobject_cast<QSlider *>(item->widget());
      slider->setValue(value);
    }

    m_current = value;
  }
}

//-----------------------------------------------------------------
void ProgressWidgetAction::setMaximumValue(int value)
{
  if(m_maxValue != value)
  {
    for(auto widget: createdWidgets())
    {
      auto item = widget->layout()->itemAt(1);
      auto slider = qobject_cast<QSlider *>(item->widget());
      slider->setMaximum(value);
    }

    m_maxValue = value;
  }
}
//-----------------------------------------------------------------
void ProgressWidgetAction::onButtonClicked(bool checked)
{
  auto button = qobject_cast<QPushButton *>(sender());
  if(checked)
  {
    button->setIcon(QIcon(":/TranslucentMPlayer/pause.svg"));
    emit pause();
  }
  else
  {
    button->setIcon(QIcon(":/TranslucentMPlayer/play.svg"));
    emit play();
  }
}

//-----------------------------------------------------------------
QWidget* ProgressWidgetAction::createWidget(QWidget* parent)
{
  auto layout = new QHBoxLayout;
  layout->setSpacing(0);
  layout->setContentsMargins(0,0,0,0);
  layout->setMargin(0);

  auto button = new QPushButton();
  button->setCheckable(true);
  button->setIcon(QIcon(":/TranslucentMPlayer/play.svg"));
  button->setFixedSize(QSize{24,24});

  auto slider = new QSlider(Qt::Horizontal);
  slider->setMinimum(0);
  slider->setMaximum(m_maxValue);
  slider->setValue(m_current);
  slider->setFixedHeight(20);

  connect(slider, SIGNAL(valueChanged(int)), this, SIGNAL(progressChanged(int)));
  connect(button, SIGNAL(clicked(bool)),     this, SLOT(onButtonClicked(bool)));

  layout->addWidget(button, 0);
  layout->addWidget(slider, 1);

  auto widget = new QWidget(parent);
  widget->setLayout(layout);

  return widget;

}
