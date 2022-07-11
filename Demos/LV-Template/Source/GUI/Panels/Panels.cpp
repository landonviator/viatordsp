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
    m_crusherBorder.setBounds(m_distortionBorder.getX() + m_distortionBorder.getWidth() + panelSpaceBetween, topMargin, panelWidth, panelHeight);
    m_toneBorder.setBounds(m_crusherBorder.getX() + m_crusherBorder.getWidth() + panelSpaceBetween, topMargin, panelWidth, panelHeight);
    m_reverbBorder.setBounds(m_toneBorder.getX() + m_toneBorder.getWidth() + panelSpaceBetween, topMargin, panelWidth, panelHeight);
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
