#pragma once

#include "../Widgets/Label.h"
#include "../Widgets/StyleSheet.h"

//==============================================================================
/*
*/
namespace viator_gui
{
    class Fader  : public juce::Slider
    {
    public:
        Fader
        (
            juce::String suffix,
            juce::String labelText,
            double rangeStart,
            double rangeEnd,
            double intervalValue,
            double returnValue
        )
        {
            initShadows();
            initProps(suffix, rangeStart, rangeEnd, intervalValue, returnValue);
            faderReturnValue = returnValue;
        }
        
        ~Fader() override
        {
            setLookAndFeel(nullptr);
        }
        
        void paint(juce::Graphics& g) override
        {
            juce::Slider::paint(g);
            
            if (isMidiSelectable || isMacroSelectable)
            {
                g.setColour(juce::Colours::purple.withAlpha(0.25f));
                g.fillRect(getLocalBounds());
                
                if (isMidiSelected || hasMidiMap || isMacroSelected || hasMacroMap)
                {
                    g.resetToDefaultState();
                    g.setColour(juce::Colours::whitesmoke.withAlpha(0.25f));
                    g.fillRect(getLocalBounds());
                }
            }
        }
        
        void updateLabelColor(juce::Colour newColor);
        
        void mouseDoubleClick (const juce::MouseEvent &event) override
        {
            if (isMidiSelectable)
            {
                isMidiSelected ? isMidiSelected = false : isMidiSelected = true;
            }
            
            setValue(faderReturnValue);
        }
        
        /** MIDI */
        void setMidiSelectable(bool sliderISSelectable)
        {
            isMidiSelectable = sliderISSelectable;
            repaint();
        }
        
        bool getIsMidiSelectable()
        {
            return isMidiSelectable;
        }
        
        void setMidiSelected(bool newSelectState)
        {
            isMidiSelected = newSelectState;
            
            if (isMidiSelected)
            {
                setMidiSelectable(false);
            }
        }
        
        bool getIsMidiSelected()
        {
            return isMidiSelected;
        }
        
        void setHasMidiMap(bool newHasMidiMap)
        {
            hasMidiMap = newHasMidiMap;
            
            if (!hasMidiMap)
            {
                setMidiSelectable(true);
            }
        }
        
        bool getHasMidiMap()
        {
            return hasMidiMap;
        }
        
        void setMidiMapToBeDeleted(bool newIsToBeDeleted)
        {
            isMidiMapToBeDeleted = newIsToBeDeleted;
        }
        
        bool getIsMidiMapToBeDeleted()
        {
            return isMidiMapToBeDeleted;
        }
        
        /** MACRO */
        void setMacroSelectable(bool sliderISSelectable)
        {
            isMacroSelectable = sliderISSelectable;
            repaint();
        }
        
        bool getIsMacroSelectable()
        {
            return isMacroSelectable;
        }
        
        void setMacroSelected(bool newSelectState)
        {
            isMacroSelected = newSelectState;
            
            if (isMacroSelected)
            {
                setMacroSelectable(false);
            }
        }
        
        bool getIsMacroSelected()
        {
            return isMacroSelected;
        }
        
        void setHasMacroMap(bool newHasMacroMap)
        {
            hasMacroMap = newHasMacroMap;
            
            if (!hasMacroMap)
            {
                setMacroSelectable(true);
            }
        }
        
        bool getHasMacroMap()
        {
            return hasMacroMap;
        }
        
        void setMacroMapToBeDeleted(bool newIsToBeDeleted)
        {
            isMacroMapToBeDeleted = newIsToBeDeleted;
        }
        
        bool getIsMacroMapToBeDeleted()
        {
            return isMacroMapToBeDeleted;
        }
        
        void forceShadow();
        
    private:
        
        /** Methods ===============================================================*/
        void mouseDown(const juce::MouseEvent &event) override
        {
            if (event.mods.isRightButtonDown())
            {
                slider.setSliderSnapsToMousePosition(false);
                setMidiMapToBeDeleted(true);
                
                setMacroMapToBeDeleted(true);
            }
            
            else
            {
                juce::Slider::mouseDown(event);
                slider.setSliderSnapsToMousePosition(true);
            }
        }
        
        void mouseUp(const juce::MouseEvent &event) override
        {
            if (event.mods.isRightButtonDown())
            {
                slider.setSliderSnapsToMousePosition(false);
                setMidiMapToBeDeleted(true);
                setMacroMapToBeDeleted(true);
            }
            
            else
            {
                juce::Slider::mouseUp(event);
                slider.setSliderSnapsToMousePosition(true);
            }
        }
        
        void mouseEnter (const juce::MouseEvent& event) override;
        void mouseExit (const juce::MouseEvent& event) override;
        
        void initProps
        (
            juce::String suffix,
            double rangeStart,
            double rangeEnd,
            double intervalValue,
            double returnValue
         );
        
        /** Fader shadow */
        void initShadows();
        
        /** Slider */
        juce::Slider slider;
        juce::FaderLAF customFader;
        
        /** Fader shadow */
        juce::DropShadow sliderShadowProperties;
        juce::DropShadowEffect sliderShadow;
        
        /** Label */
        Label trimLabel {""};
        
        /** Midi Map*/
        bool isMidiSelectable = false;
        bool isMidiSelected = false;
        bool hasMidiMap = false;
        bool isMidiMapToBeDeleted = false;
        
        /** Macro Map*/
        bool isMacroSelectable = false;
        bool isMacroSelected = false;
        bool hasMacroMap = false;
        bool isMacroMapToBeDeleted = false;
        
        double faderReturnValue;
        
        juce::Colour accentColor = juce::Colours::whitesmoke;
    };
}
