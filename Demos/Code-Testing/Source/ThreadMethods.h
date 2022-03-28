/*
  ==============================================================================

    ThreadMethods.h
    Created: 28 Mar 2022 3:13:23pm
    Author:  Landon Viator

  ==============================================================================
*/

#pragma once

class MeterThread : public juce::Thread
{
        
    public:
    
        MeterThread() : juce::Thread ("Meter Thread")
        {
            
        }
        
        void run() override
        {
            timeMethods();
            signalThreadShouldExit();
        }
        
        void timeMethods()
        {
            currentCount = 0;
            
            auto start = std::chrono::high_resolution_clock::now();
            ifLoop();
            auto stop = std::chrono::high_resolution_clock::now();
            auto phaseConditional = duration_cast<std::chrono::microseconds>(stop - start);
            std::cout << "The IF took " << phaseConditional.count() * 0.000001 << " seconds to execute" << std::endl;
            auto rawCSecs = phaseConditional.count() * 0.000001;
                
            start = std::chrono::high_resolution_clock::now();
            switchLoop();
            stop = std::chrono::high_resolution_clock::now();
            auto phaseExpression = duration_cast<std::chrono::microseconds>(stop - start);
            std::cout << "The SWITCH took " << phaseExpression.count() * 0.000001 << " seconds to execute" << std::endl;
            auto rawESecs = phaseExpression.count() * 0.000001;
                    
            if (rawCSecs < rawESecs)
            {
                auto increase = rawESecs - rawCSecs;
                auto percentage = increase / rawESecs * 100.0;
                std::cout << "The IF version was faster by: " << percentage << "%." << std::endl;
            }
                    
            else
            {
                auto increase = rawCSecs - rawESecs;
                auto percentage = increase / rawCSecs * 100.0;
                std::cout << "The SWITCH was faster by: " << percentage << "%." << std::endl;
            }
        }
            
        void ifLoop()
        {
            for (int i {0}; i < runLength; ++i)
            {
                ifCheck();
                currentCount++;
                currentPercentage = currentCount / (runLength * 2);
            }
        }
            
        void switchLoop()
        {
            for (int i {0}; i < runLength; ++i)
            {
                switchCheck();
                currentCount++;
                currentPercentage = currentCount / (runLength * 2);
            }
        }
            
        void ifCheck()
        {
            if (valueCheck)
            {
                auto value = std::pow(std::atan(0.5), 10);
                value++;
            }
                    
            else
            {
                auto value = std::pow(std::atan(0.5), 10);
                value++;
            }
        }
            
        void switchCheck()
        {
            switch (valueCheck)
            {
                case 1:
                {
                    auto value = std::pow(std::atan(0.5), 10);
                    value++;
                    break;
                }
                        
                case 0:
                {
                    auto value = std::pow(std::atan(0.5), 10);
                    value++;
                    break;
                }
            }
        }
                    
    double currentPercentage {0};
    double currentCount;
    int valueCheck {0};
    int runLength {10000000};
        
};
