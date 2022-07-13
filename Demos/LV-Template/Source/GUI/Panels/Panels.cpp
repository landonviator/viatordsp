/*
  ==============================================================================

    DistortionPanel.cpp
    Created: 8 Jul 2022 4:30:10pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "../../PluginEditor.h"

void LVTemplateAudioProcessorEditor::setPanelLayout()
{
    /** Panels */
    auto leftMargin = getWidth() * 0.055;
    auto topMargin = getHeight() * 0.08 * 1.3;
    auto panelWidth = getWidth() * 0.21;
    auto panelHeight = getHeight() * 0.85;
    auto panelSpaceBetween = panelWidth * 0.085;
    
    m_distortionBorder.setBounds(leftMargin, topMargin, panelWidth, panelHeight);
    m_toneBorder.setBounds(m_distortionBorder.getX() + m_distortionBorder.getWidth() + panelSpaceBetween, topMargin, panelWidth, panelHeight);
    m_reverbBorder.setBounds(m_toneBorder.getX() + m_toneBorder.getWidth() + panelSpaceBetween, topMargin, panelWidth * 2.0, panelHeight);
}

void LVTemplateAudioProcessorEditor::setDistortionGroupLayout()
{
    const auto titleSize = 0.1;
    const auto toggleTop = 1.08;
    const auto toggleSize = getWidth() * 0.04;
    const auto labelWidth = getWidth() * 0.12;
    const auto labelHeight = getHeight() * 0.05;
    const auto menuX = m_distortionBorder.getX() * 1.2;
    const auto menuY = m_distortionBorder.getY() * 1.94;
    const auto menuWidth = m_distortionBorder.getWidth() * 0.9;
    const auto menuHeight = m_distortionBorder.getHeight() * 0.08;
    const auto dialX = m_distortionBorder.getX() * 1.5;
    const auto dialY = m_distortionBorder.getY() * 3.0;
    const auto dialSize = m_distortionBorder.getWidth() * 0.7;
    
    m_distortionTitle.setBounds(m_distortionBorder.getX(), m_distortionBorder.getY(), m_distortionBorder.getWidth(), m_distortionBorder.getHeight() * titleSize);
    m_distortionToggle.setBounds(m_distortionBorder.getX(), m_distortionBorder.getY() * toggleTop, toggleSize, toggleSize);
    m_distortionLabel.setBounds(m_distortionToggle.getX() + m_distortionToggle.getWidth(), m_distortionToggle.getY() * 1.17, labelWidth, labelHeight);
    m_distortionMenu.setBounds(menuX, menuY, menuWidth, menuHeight);
    m_driveDial.setBounds(dialX, dialY, dialSize, dialSize);
    m_mixDial.setBounds(dialX, m_driveDial.getY() + m_driveDial.getHeight(), dialSize, dialSize);
}

void LVTemplateAudioProcessorEditor::setToneGroupLayout()
{
    const auto titleSize = 0.1;
    const auto toggleTop = 1.08;
    const auto toggleSize = getWidth() * 0.04;
    const auto labelWidth = getWidth() * 0.12;
    const auto labelHeight = getHeight() * 0.05;
    const auto dialX = m_toneBorder.getX() * 1.158;
    const auto dialY = m_toneBorder.getY() * 2.0;
    const auto dialSize = m_toneBorder.getWidth() * 0.59;
    const auto buttonX = m_toneBorder.getX() * 1.56;
    const auto buttonY = m_toneBorder.getY() * 1.27;
    const auto buttonWidth = m_toneBorder.getWidth() * 0.22;
    const auto buttonHeight = buttonWidth * 0.5;
    
    m_toneTitle.setBounds(m_toneBorder.getX(), m_toneBorder.getY(), m_toneBorder.getWidth(), m_toneBorder.getHeight() * titleSize);
    m_toneToggle.setBounds(m_toneBorder.getX(), m_toneBorder.getY() * toggleTop, toggleSize, toggleSize);
    m_toneLabel.setBounds(m_toneToggle.getX() + m_toneToggle.getWidth() * 1.17, m_toneToggle.getY() * 1.17, labelWidth, labelHeight);
    m_prepostButton.setBounds(buttonX, buttonY, buttonWidth, buttonHeight);
    
    m_tiltSlider.setBounds(dialX, dialY, dialSize, dialSize);
    m_toneDial.setBounds(dialX, m_tiltSlider.getY() + m_tiltSlider.getHeight(), dialSize, dialSize);
    m_cutoffDial.setBounds(dialX, m_toneDial.getY() + m_toneDial.getHeight(), dialSize, dialSize);
}

void LVTemplateAudioProcessorEditor::setReverbGroupLayout()
{
    const auto titleSize = 0.1;
    const auto toggleTop = 1.08;
    const auto toggleSize = getWidth() * 0.04;
    const auto labelWidth = getWidth() * 0.12;
    const auto labelHeight = getHeight() * 0.05;
    const auto dialX = m_reverbBorder.getX() * 1.12;
    const auto dialY = m_reverbBorder.getY() * 2.55;
    const auto dialSize = m_reverbBorder.getWidth() * 0.36;
    
    m_reverbTitle.setBounds(m_reverbBorder.getX(), m_reverbBorder.getY(), m_reverbBorder.getWidth(), m_reverbBorder.getHeight() * titleSize);
    m_reverbToggle.setBounds(m_reverbBorder.getX(), m_reverbBorder.getY() * toggleTop, toggleSize, toggleSize);
    m_reverbLabel.setBounds(m_reverbToggle.getX() + m_reverbToggle.getWidth() * 3.75, m_reverbToggle.getY() * 1.17, labelWidth, labelHeight);
    
    m_sizeDial.setBounds(dialX, dialY, dialSize, dialSize);
    m_widthDial.setBounds(dialX, m_sizeDial.getY() + m_sizeDial.getHeight(), dialSize, dialSize);
    m_dampDial.setBounds(m_sizeDial.getX() + m_sizeDial.getWidth(), m_sizeDial.getY(), dialSize, dialSize);
    m_blendDial.setBounds(m_dampDial.getX(), m_dampDial.getY() + m_dampDial.getHeight(), dialSize, dialSize);
}
