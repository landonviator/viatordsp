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
            loop1();
            auto stop = std::chrono::high_resolution_clock::now();
            auto phaseConditional = duration_cast<std::chrono::microseconds>(stop - start);
            std::cout << "The Viator DSP took " << phaseConditional.count() * 0.000001 << " seconds to execute" << std::endl;
            auto rawCSecs = phaseConditional.count() * 0.000001;
                
            start = std::chrono::high_resolution_clock::now();
            loop2();
            stop = std::chrono::high_resolution_clock::now();
            auto phaseExpression = duration_cast<std::chrono::microseconds>(stop - start);
            std::cout << "The sign took " << phaseExpression.count() * 0.000001 << " seconds to execute" << std::endl;
            auto rawESecs = phaseExpression.count() * 0.000001;
                    
            if (rawCSecs < rawESecs)
            {
                auto increase = rawESecs - rawCSecs;
                auto percentage = increase / rawESecs * 100.0;
                std::cout << "The Viator DSP version was faster by: " << percentage << "%." << std::endl;
            }
                    
            else
            {
                auto increase = rawCSecs - rawESecs;
                auto percentage = increase / rawCSecs * 100.0;
                std::cout << "The JLIMIT was faster by: " << percentage << "%." << std::endl;
            }
        }
            
        void loop1()
        {
            for (int i {0}; i < runLength; ++i)
            {
                auto value = viator_utils::utils::clipData(i);
                
                for (int i {0}; i < runLength; ++i)
                {
                    value = viator_utils::utils::clipData(i);
                    
                    for (int i {0}; i < runLength; ++i)
                    {
                        value = viator_utils::utils::clipData(i);
                    }
                }
                
                currentCount++;
                currentPercentage = currentCount / (runLength * 2);
            }
        }
            
        void loop2()
        {
            for (int i {0}; i < runLength; ++i)
            {
                auto value = std::copysign(1.0, -0.99);
                
                for (int i {0}; i < runLength; ++i)
                {
                    value = std::copysign(1.0, -0.99);
                    
                    for (int i {0}; i < runLength; ++i)
                    {
                        value = std::copysign(1.0, -0.99);
                    }
                }
                
                currentCount++;
                currentPercentage = currentCount / (runLength * 2);
            }
        }
    
    //currentCount++;
    //currentPercentage = currentCount / (runLength * 2);
    double currentPercentage {0};
    double currentCount;
    int runLength {1000};
        
};
