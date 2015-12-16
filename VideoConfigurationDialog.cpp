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

#define VALUE_TEXT(value) QString("%1%").arg(value)

//-----------------------------------------------------------------
VideoConfigurationDialog::VideoConfigurationDialog(PlayerManager *manager, QWidget *parent, Qt::WindowFlags flags)
: QDialog  {parent, flags}
, m_manager{manager}
{
  setupUi(this);

  m_positionComboBox->insertItems(0, m_manager->widgetPositionNames());
  m_positionComboBox->setCurrentIndex(m_manager->widgetPosition());

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
  m_manager->setWidgetPosition(index);
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
