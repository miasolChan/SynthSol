

#pragma once

#include <JuceHeader.h>

class PhaserData
{
public:
    void prepare(const juce::dsp::ProcessSpec& spec);
    void setPhaserParameters(const float rate, const float depth, const float centerFreq,
        const float fdbk, const float mix);
    void process(juce::AudioBuffer<float>& buffer);
    void reset();
    void createParamLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout);

private:
    juce::dsp::Phaser<float> phaser; 
    bool isPrepared { false };
};