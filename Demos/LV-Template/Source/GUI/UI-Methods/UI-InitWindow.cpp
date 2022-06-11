#include "../../PluginEditor.h"

void LVTemplateAudioProcessorEditor::initWindow()
{
    // Grab the window instance and create a rectangle
    juce::Rectangle<int> r = juce::Desktop::getInstance().getDisplays().getPrimaryDisplay()->userArea;
    
    // Using the width is more useful than the height, because we know the height will always be < than width
    int x = r.getWidth();
    
    auto width = 0;
    
    if (r.getWidth() <= 1920)
    {
        width = x * 0.7;
    }
    
    else
    {
        width = x * 0.4f;
    }
    
    auto height = width * 0.7;
    
    //Making the window resizable by aspect ratio and setting size
    AudioProcessorEditor::setResizable(true, true);
    AudioProcessorEditor::setResizeLimits(width * 0.5, height * 0.5, width * 1.25, height * 1.25);
    AudioProcessorEditor::getConstrainer()->setFixedAspectRatio(1.42857);
    
    if (audioProcessor.windowWidth != 0.0)
    {
        setSize(audioProcessor.windowWidth, audioProcessor.windowHeight);
    }
        
    else
    {
        setSize (width, height);
    }
    
    constructorFinished = true;
}
