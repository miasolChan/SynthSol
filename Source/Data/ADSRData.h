
#pragma once
#include <JuceHeader.h>
#include "Settings/AdsrSettings.h"
class ADSRData : public juce::ADSR 
{
public:
    //设置ADSRlayout
    void createParamLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout);
    //获取APVTS
    void getParamValue(juce::AudioProcessorValueTreeState& apvts);
    //设置ADSR的值
    void updateADSR();
    //用于Process中的更新信息
    void voiceUpdate(juce::AudioProcessorValueTreeState& apvts);

private:

    AdsrSettings adsrSettings;
    juce::ADSR::Parameters adsrParams;
};