

#pragma once
#include <JuceHeader.h>

class GainData
{
public:
    void prepare(const juce::dsp::ProcessSpec& spec);
    void setGainLevel(const float newGain);
    void process(juce::AudioBuffer<float>& buffer);
    void reset();
    //设置layout
    void createParamLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout);
    //获取APVTS
    void getParamValue(juce::AudioProcessorValueTreeState& apvts);
    //用于Process中的更新信息
    void voiceUpdate(juce::AudioProcessorValueTreeState& apvts);
private:
    float gainVal;
    juce::dsp::Gain<float> gain;
    bool isPrepared{ false };
};