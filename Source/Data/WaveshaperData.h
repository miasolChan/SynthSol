

#pragma once
#include <JuceHeader.h>

class WaveshaperData 
{
public:
    void prepare(juce::dsp::ProcessSpec& proc);
    void process(juce::AudioBuffer<float>& buffer);
    void updateDistortion(const int distortionType);
    void reset();
    //设置Layout
    void createParamLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout);
    //获取APVTS
    void getParamValue(juce::AudioProcessorValueTreeState& apvts);
    //用于Process中的更新信息
    void voiceUpdate(juce::AudioProcessorValueTreeState& apvts);
private:
    float distortionType;
    juce::dsp::WaveShaper<float> distortion;
};