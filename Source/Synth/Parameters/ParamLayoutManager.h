

#pragma once
#include <JuceHeader.h>
#include "../Source/SynthSound.h"
#include "../Source/SynthVoice.h"

#include "../Source/Data/ADSRData.h"
#include "../Source/Data/ChorusData.h"
#include"../Source/Data/CompressorData.h"
#include"../Source/Data/FilterData.h"
#include"../Source/Data/GainData.h"
#include "../Source/Data/OscData.h"
#include "../Source/Data/PhaserData.h"
#include "../Source/Data/ReverbData.h"
#include"../Source/Data/WaveshaperData.h"

class ParamLayoutManager
{
public:


    void createAllParamLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout);

private:
    ADSRData adsr;
    ChorusData chorus;
    CompressorData comp;
    FilterData filter;
    GainData gain;
    OscData osc;
    PhaserData phaser;
    ReverbData reverb;
    WaveshaperData wshaper;

};
