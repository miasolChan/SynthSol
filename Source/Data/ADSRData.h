
#pragma once
#include <JuceHeader.h>
#include "Settings/AdsrSettings.h"
class ADSRData : public juce::ADSR 
{
public:
    //����ADSRlayout
    void createParamLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout);
    //��ȡAPVTS
    void getParamValue(juce::AudioProcessorValueTreeState& apvts);
    //����ADSR��ֵ
    void updateADSR();
    //����Process�еĸ�����Ϣ
    void voiceUpdate(juce::AudioProcessorValueTreeState& apvts);

private:

    AdsrSettings adsrSettings;
    juce::ADSR::Parameters adsrParams;
};