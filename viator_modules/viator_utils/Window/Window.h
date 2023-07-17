#pragma once
#include <JuceHeader.h>

namespace viator_utils
{
class PluginWindow
{
public:
    
    /**
     * @brief Set up the plugin window size based on the user's screen size.
     *
     * @author Landon Viator
     *
     * @param pluginWidth The saved plugin width variable saved in the plugin's variable tree.
     * @param pluginHeight The saved plugin height variable saved in the plugin's variable tree.
     * @param editor A reference to the plugin editor so its static methods can be used.
     */
    template <typename T>
    static inline void setPluginWindowSize(T pluginWidth, T pluginHeight, juce::AudioProcessorEditor& editor, double ratio, double mult)
    {
        // Grab the window instance and create a rectangle
        juce::Rectangle<float> r = juce::Desktop::getInstance().getDisplays().getPrimaryDisplay()->userArea.toFloat();

        float width = 0.0;
        
        // loops through and match screen size
        for (const auto& entry : widthThresholds)
        {
            if (r.getWidth() >= entry.first)
            {
                width = r.getWidth() * entry.second  * mult;
                break;
            }
        }
        
        // set size to 0.9 if less than 1080
        if (width == 0.0)
        {
            width = r.getWidth() * 0.9 * mult;
        }
        
        // make height half of the width
        const float height = width * (1.0 / ratio);

        // Set the size
        if (pluginWidth != 0.0)
        {
            editor.setSize(pluginWidth, pluginHeight);
        }
            
        else
        {
            editor.setSize (width, height);
        }
        
        editor.setResizable(true, true);
        editor.getConstrainer()->setFixedAspectRatio(ratio);
        editor.setResizeLimits(width * 0.65, height * 0.65, width * 2.0, height * 2.0);
    }
    
private:
    static inline std::vector<std::pair<float, float>> widthThresholds = {
        {7680.0f, 0.3},
        {5120.0f, 0.4},
        {3840.0f, 0.5},
        {2560.0f, 0.6},
        {1920.0f, 0.7},
        {1080.0f, 0.8}
    };
};
}
