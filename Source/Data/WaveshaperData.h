

#pragma once
#include <JuceHeader.h>

class WaveshaperData 
{
public:
    void prepare(juce::dsp::ProcessSpec& proc);
    void process(juce::AudioBuffer<float>& buffer);
    void updateDistortion(const int distortionType);
    void reset();
    //����Layout
    void createParamLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout);
    //��ȡAPVTS
    void getParamValue(juce::AudioProcessorValueTreeState& apvts);
    //����Process�еĸ�����Ϣ
    void voiceUpdate(juce::AudioProcessorValueTreeState& apvts);
private:
    float distortionType;
    juce::dsp::WaveShaper<float> distortion;
};