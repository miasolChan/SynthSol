

#pragma once

#include <JuceHeader.h>

class CompressorData
{
public:
    void prepare(const juce::dsp::ProcessSpec& spec);
    void setCompressorParameters(const float threshold, const float ratio,
        const float attack, const float release);
    void process(juce::AudioBuffer<float>& buffer);
    void reset();
    void createParamLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout);
private:
    juce::dsp::Compressor<float> comp;
    bool isPrepared{ false };
};