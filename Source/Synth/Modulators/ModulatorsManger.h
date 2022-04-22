

#pragma once
#include "../Source/Data/ADSRData.h"
#include "../Source/Data/OscData.h"
#include "../Source/Data/FilterData.h"
#include "../Source/Data/WaveshaperData.h"
#include "../Source/Data/ReverbData.h"
#include "../Source/Data/GainData.h"
class ModulatorsManager
{
public:
    ModulatorsManager() {};
    ~ModulatorsManager() {};
    void voiceUpdateAllModulators(juce::AudioProcessorValueTreeState& apvts, double sampleRate);

private:
    OscData osc;
    ADSRData adsr;
    FilterData filter;
    WaveshaperData distortion;
    GainData gain;
};