

#pragma once
#include <JuceHeader.h>

class ChorusData
{
public:
    void prepare(const juce::dsp::ProcessSpec& spec);
    void setChorusParameters(const float rate, const float depth, const float centerDelay,
        const float fdbk, const float mix);
    void process(juce::AudioBuffer<float>& buffer);
    void reset();
    void createParamLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout);
private:
    juce::dsp::Chorus<float> chorus;
    bool isPrepared{ false };
};