/*
 File: VideoConfigurationDialog.cpp
 Created on: 14/12/2015
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
#include "VideoConfigurationDialog.h"
#include "PlayerManager.h"

// Qt
#include <QString>
#include <QRect>
#include <QApplication>
#include <QDesktopWidget>

#define VALUE_TEXT(value) QString("%1%").arg(value)

const QStringList VideoConfigurationDialog::POSITION_NAMES = { QString("Top Left"),
                                                               QString("Top Center"),
                                                               QString("Top Right"),
                                                               QString("Center Left"),
                                                               QString("Center"),
                                                               QString("Center Right"),
                                                               QString("Bottom Left"),
                                                               QString("Bottom Center"),
                                                               QString("Bottom Right") };

//-----------------------------------------------------------------
VideoConfigurationDialog::VideoConfigurationDialog(PlayerManager *manager, QWidget *parent, Qt::WindowFlags flags)
: QDialog  {parent, flags}
, m_manager{manager}
{
  setupUi(this);

  initPositionComboBox();
  m_positionComboBox ->setCurrentIndex(m_widgetPositions.indexOf(m_manager->widgetPosition()));

  connectSignals();

  m_opacitySlider    ->setValue(m_manager->opacity());
  m_sizeSlider       ->setValue(m_manager->size());
  m_volumeSlider     ->setValue(m_manager->volume());
  m_brightessSlider  ->setValue(m_manager->brightness());
  m_contrastSlider   ->setValue(m_manager->contrast());
  m_gammaSlider      ->setValue(m_manager->gamma());
  m_hueSlider        ->setValue(m_manager->hue());
  m_saturationSlider ->setValue(m_manager->saturation());
  m_subtitlesCheckbox->setChecked(m_manager->subtitlesEnabled());
}

//-----------------------------------------------------------------
void VideoConfigurationDialog::onOpacityValueChanged(int value)
{
  m_opacityValue->setText(VALUE_TEXT(value));

  m_manager->setOpacity(value);
}

//-----------------------------------------------------------------
void VideoConfigurationDialog::onSizeValueChanged(int value)
{
  m_sizeValue->setText(VALUE_TEXT(value));

  m_manager->setSize(value);

  computeDesktopWidgetPositions();
  m_manager->setWidgetPosition(m_widgetPositions.at(m_positionComboBox->currentIndex()));
}

//-----------------------------------------------------------------
void VideoConfigurationDialog::onVolumeValueChanged(int value)
{
  m_volumeValue->setText(VALUE_TEXT(value));

  m_manager->setVolume(value);
}

//-----------------------------------------------------------------
void VideoConfigurationDialog::onBrightnessValueChanged(int value)
{
  m_brightessValue->setText(VALUE_TEXT(value));

  m_manager->setBrightness(value);
}

//-----------------------------------------------------------------
void VideoConfigurationDialog::onContrastValueChanged(int value)
{
  m_contrastValue->setText(VALUE_TEXT(value));

  m_manager->setContrast(value);
}

//-----------------------------------------------------------------
void VideoConfigurationDialog::onGammaValueChanged(int value)
{
  m_gammaValue->setText(VALUE_TEXT(value));

  m_manager->setGamma(value);
}

//-----------------------------------------------------------------
void VideoConfigurationDialog::onHueValueChanged(int value)
{
  m_hueValue->setText(VALUE_TEXT(value));

  m_manager->setHue(value);
}

//-----------------------------------------------------------------
void VideoConfigurationDialog::onSaturationValueChanged(int value)
{
  m_saturationValue->setText(VALUE_TEXT(value));

  m_manager->setSaturation(value);
}

//-----------------------------------------------------------------
void VideoConfigurationDialog::onSubtitlesStateChanged(int state)
{
  auto enabled = (state == Qt::Checked);

  m_manager->enableSubtitles(enabled);
}

//-----------------------------------------------------------------
void VideoConfigurationDialog::onPositionChanged(int index)
{
  m_manager->setWidgetPosition(m_widgetPositions[index]);
}

//-----------------------------------------------------------------
void VideoConfigurationDialog::connectSignals()
{
  connect(m_opacitySlider,     SIGNAL(valueChanged(int)),        this, SLOT(onOpacityValueChanged(int)));
  connect(m_sizeSlider,        SIGNAL(valueChanged(int)),        this, SLOT(onSizeValueChanged(int)));
  connect(m_volumeSlider,      SIGNAL(valueChanged(int)),        this, SLOT(onVolumeValueChanged(int)));
  connect(m_brightessSlider,   SIGNAL(valueChanged(int)),        this, SLOT(onBrightnessValueChanged(int)));
  connect(m_contrastSlider,    SIGNAL(valueChanged(int)),        this, SLOT(onContrastValueChanged(int)));
  connect(m_gammaSlider,       SIGNAL(valueChanged(int)),        this, SLOT(onGammaValueChanged(int)));
  connect(m_hueSlider,         SIGNAL(valueChanged(int)),        this, SLOT(onHueValueChanged(int)));
  connect(m_saturationSlider,  SIGNAL(valueChanged(int)),        this, SLOT(onSaturationValueChanged(int)));
  connect(m_subtitlesCheckbox, SIGNAL(stateChanged(int)),        this, SLOT(onSubtitlesStateChanged(int)));
  connect(m_positionComboBox,  SIGNAL(currentIndexChanged(int)), this, SLOT(onPositionChanged(int)));
}

//-----------------------------------------------------------------
void VideoConfigurationDialog::computeDesktopWidgetPositions()
{
  m_widgetPositions.clear();

  auto desktop = QApplication::desktop();
  computePositions(desktop->geometry());

  for (int i = 0; i < desktop->numScreens(); ++i)
  {
    computePositions(desktop->screenGeometry(i));
  }
}

//-----------------------------------------------------------------
void VideoConfigurationDialog::computePositions(const QRect &rect)
{
  auto widgetSize = m_manager->videoSize();

  for(int y: {rect.y(), rect.y()+(rect.height()-widgetSize.height())/2, rect.y()+rect.height()-widgetSize.height()})
  {
    for(int x: {rect.x(), rect.x()+(rect.width()-widgetSize.width())/2, rect.x()+rect.width()-widgetSize.width()})
    {
      m_widgetPositions << QPoint{x,y};
    }
  }

}

//-----------------------------------------------------------------
void VideoConfigurationDialog::initPositionComboBox()
{
  QStringList positionNames;

  for(auto position: POSITION_NAMES)
  {
    positionNames << QString("Global ") + position;
  }

  auto desktop = QApplication::desktop();
  for (int i = 0; i < desktop->numScreens(); ++i)
  {
    for(auto position: POSITION_NAMES)
    {
      positionNames << QString("Monitor %1 ").arg(i) + position;
    }
  }

  computeDesktopWidgetPositions();

  m_positionComboBox->insertItems(0, positionNames);
}
