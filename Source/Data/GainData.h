

#pragma once
#include <JuceHeader.h>

class GainData
{
public:
    void prepare(const juce::dsp::ProcessSpec& spec);
    void setGainLevel(const float newGain);
    void process(juce::AudioBuffer<float>& buffer);
    void reset();
    //����layout
    void createParamLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout);
    //��ȡAPVTS
    void getParamValue(juce::AudioProcessorValueTreeState& apvts);
    //����Process�еĸ�����Ϣ
    void voiceUpdate(juce::AudioProcessorValueTreeState& apvts);
private:
    float gainVal;
    juce::dsp::Gain<float> gain;
    bool isPrepared{ false };
};