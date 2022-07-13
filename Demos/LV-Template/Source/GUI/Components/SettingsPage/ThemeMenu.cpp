/*
  ==============================================================================

    ThemeMenu.cpp
    Created: 11 Jun 2022 12:29:53am
    Author:  Landon Viator

  ==============================================================================
*/

#include "SettingsPage.h"

void SettingsPage::setThemeMenuProps()
{
    m_themeMenu.setText("Themes");
    m_themeMenu.setTextWhenNothingSelected("Themes");
    m_themeMenu.addSectionHeading("Dark");
    m_themeMenu.addItem("Dracula", 1);
    m_themeMenu.addItem("Prime Dark", 2);
    m_themeMenu.addItem("Tokyo Lofi", 3);
    m_themeMenu.addItem("Winter", 4);
    m_themeMenu.addItem("Foxy", 5);
    m_themeMenu.addItem("Purp", 6);
    m_themeMenu.addItem("Dull", 7);
    m_themeMenu.onChange = [this]()
    {
        switch (m_themeMenu.getSelectedItemIndex())
        {
            case 0:
            {
                setPluginTheme(Theme::kDracula);
                getParentComponent()->repaint();
                audioProcessor.variableTree.setProperty("colortheme", 0, nullptr);
                break;
            }
                
            case 1:
            {
                setPluginTheme(Theme::kPrimeDark);
                getParentComponent()->repaint();
                audioProcessor.variableTree.setProperty("colortheme", 1, nullptr);
                break;
            }
                
            case 2:
            {
                setPluginTheme(Theme::kTokyoLofi);
                getParentComponent()->repaint();
                audioProcessor.variableTree.setProperty("colortheme", 2, nullptr);
                break;
            }
                
            case 3:
            {
                setPluginTheme(Theme::kWinter);
                getParentComponent()->repaint();
                audioProcessor.variableTree.setProperty("colortheme", 3, nullptr);
                break;
            }
                
            case 4:
            {
                setPluginTheme(Theme::kFoxy);
                getParentComponent()->repaint();
                audioProcessor.variableTree.setProperty("colortheme", 4, nullptr);
                break;
            }
                
            case 5:
            {
                setPluginTheme(Theme::kPurp);
                getParentComponent()->repaint();
                audioProcessor.variableTree.setProperty("colortheme", 5, nullptr);
                break;
            }
                
            case 6:
            {
                setPluginTheme(Theme::kDull);
                getParentComponent()->repaint();
                audioProcessor.variableTree.setProperty("colortheme", 6, nullptr);
                break;
            }
        }
    };
    
    m_themeMenu.setSelectedItemIndex(static_cast<int>(audioProcessor.variableTree.getProperty("colortheme")));
}
