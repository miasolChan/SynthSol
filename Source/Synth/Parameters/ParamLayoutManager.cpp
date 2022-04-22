

#include "ParamLayoutManager.h"


void ParamLayoutManager::createAllParamLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout)
{
    adsr.createParamLayout(layout);
    chorus.createParamLayout(layout);
    comp.createParamLayout(layout);
    filter.createParamLayout(layout);
    gain.createParamLayout(layout);
    osc.createParamLayout(layout);
    phaser.createParamLayout(layout);
    reverb.createParamLayout(layout);
    wshaper.createParamLayout(layout);
}
