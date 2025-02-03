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
#include <ProgressWidgetAction.h>

// Qt
#include <QObject>
#include <QSlider>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>

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
    blockSignals(true);
    for(auto widget: createdWidgets())
    {
      auto layout = widget->layout()->itemAt(0)->layout();
      auto slider = qobject_cast<QSlider *>(layout->itemAt(1)->widget());
      slider->setValue(value);

      layout = widget->layout()->itemAt(1)->layout();
      auto label = qobject_cast<QLabel *>(layout->itemAt(0)->widget());
      label->setText(QString("%1:%2:%3").arg(value/3600, 2, 10, QChar('0')).arg((value/60)%60, 2, 10, QChar('0')).arg(value%60, 2, 10, QChar('0')));
    }
    blockSignals(false);

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
      auto layout = widget->layout()->itemAt(0)->layout();
      auto slider = qobject_cast<QSlider *>(layout->itemAt(1)->widget());
      slider->setMaximum(value);

      layout = widget->layout()->itemAt(1)->layout();
      auto label = qobject_cast<QLabel *>(layout->itemAt(2)->widget());
      label->setText(QString("%1:%2:%3").arg(value/3600, 2, 10, QChar('0')).arg((value/60)%60, 2, 10, QChar('0')).arg(value%60, 2, 10, QChar('0')));
    }

    m_maxValue = value;
  }
}

//-----------------------------------------------------------------
void ProgressWidgetAction::reset()
{
  blockSignals(true);

  for(auto widget: createdWidgets())
  {
    auto layout = widget->layout()->itemAt(0)->layout();
    auto button = qobject_cast<QPushButton *>(layout->itemAt(0)->widget());
    button->setChecked(false);
    button->setIcon(QIcon(":/TranslucentMPlayer/pause.svg"));

    auto slider = qobject_cast<QSlider *>(layout->itemAt(1)->widget());
    slider->setMaximum(0);
    slider->setValue(0);

    layout = widget->layout()->itemAt(1)->layout();
    auto label = qobject_cast<QLabel *>(layout->itemAt(2)->widget());
    label->setText("00:00:00");
  }

  m_current = 0;
  m_maxValue = 100;

  blockSignals(false);
}

//-----------------------------------------------------------------
void ProgressWidgetAction::onButtonClicked(bool checked)
{
  auto button = qobject_cast<QPushButton *>(sender());
  if(checked)
  {
    button->setIcon(QIcon(":/TranslucentMPlayer/play.svg"));
    emit pause();
  }
  else
  {
    button->setIcon(QIcon(":/TranslucentMPlayer/pause.svg"));
    emit play();
  }
}

//-----------------------------------------------------------------
void ProgressWidgetAction::onProgressChanged(int value)
{
  for(auto widget: createdWidgets())
  {
    auto layout = widget->layout()->itemAt(1)->layout();
    auto label = qobject_cast<QLabel *>(layout->itemAt(0)->widget());
    label->setText(QString("%1:%2:%3").arg(value/3600, 2, 10, QChar('0')).arg((value/60)%60, 2, 10, QChar('0')).arg(value%60, 2, 10, QChar('0')));
  }

  emit progressChanged(value);
}

//-----------------------------------------------------------------
QWidget* ProgressWidgetAction::createWidget(QWidget* parent)
{
  auto layout = new QVBoxLayout;
  layout->setSpacing(3);
  layout->setContentsMargins(3,3,3,3);

  auto layout1 = new QHBoxLayout;
  layout1->setSpacing(0);
  layout1->setContentsMargins(0,0,0,0);

  auto button = new QPushButton();
  button->setCheckable(true);
  button->setIcon(QIcon(":/TranslucentMPlayer/pause.svg"));
  button->setFixedSize(QSize{24,24});

  auto slider = new QSlider(Qt::Horizontal);
  slider->setMinimum(0);
  slider->setMaximum(m_maxValue);
  slider->setValue(m_current);
  slider->setFixedHeight(20);

  connect(slider, SIGNAL(valueChanged(int)), this, SLOT(onProgressChanged(int)));
  connect(button, SIGNAL(clicked(bool)),     this, SLOT(onButtonClicked(bool)));

  layout1->addWidget(button, 0);
  layout1->addWidget(slider, 1);

  auto layout2 = new QHBoxLayout;
  layout2->setSpacing(0);
  layout2->setContentsMargins(0,0,0,0);

  auto currentTime = new QLabel();
  currentTime->setText(QString("%1:%2:%3").arg(m_current/3600, 2, 10, QChar('0')).arg((m_current/60)%60, 2, 10, QChar('0')).arg(m_current%60, 2, 10, QChar('0')));
  currentTime->setAlignment(Qt::AlignHCenter);

  auto separator = new QLabel();
  separator->setText("/");

  auto totalTime = new QLabel();
  totalTime->setText(QString("%1:%2:%3").arg(m_maxValue/3600, 2, 10, QChar('0')).arg((m_maxValue/60)%60, 2, 10, QChar('0')).arg(m_maxValue%60, 2, 10, QChar('0')));
  totalTime->setAlignment(Qt::AlignHCenter);

  layout2->addWidget(currentTime, 1);
  layout2->addWidget(separator, 0);
  layout2->addWidget(totalTime, 1);

  layout->addLayout(layout1);
  layout->addLayout(layout2);

  auto widget = new QWidget(parent);
  widget->setLayout(layout);

  return widget;
}
