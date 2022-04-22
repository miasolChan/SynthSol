#include "ADSRData.h"

//����ADSRlayout
void ADSRData::createParamLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout)
{
    layout.add(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack",
        juce::NormalisableRange<float>{0.0f, 1.0f, 0.01f }, 0.06f));

    layout.add(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay",
        juce::NormalisableRange<float>{0.01f, 1.0f, 0.01f }, 1.0f));

    layout.add(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain",
        juce::NormalisableRange<float>{0.0f, 1.0f, 0.01f }, 1.0f));

    layout.add(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release",
        juce::NormalisableRange<float>{0.01f, 5.0f, 0.01f }, 0.25f));
}

//��ȡAPVTS
void ADSRData::getParamValue(juce::AudioProcessorValueTreeState& apvts)
{
    adsrSettings.setAttack(apvts.getRawParameterValue("ATTACK")->load());
    adsrSettings.setDecay(apvts.getRawParameterValue("DECAY")->load());
    adsrSettings.setSustain( apvts.getRawParameterValue("SUSTAIN")->load());
    adsrSettings.setRelease( apvts.getRawParameterValue("RELEASE")->load());
}

//����ADSR��ֵ
void ADSRData::updateADSR()
{
    adsrParams.attack = adsrSettings.getAttack();
    adsrParams.decay = adsrSettings.getDecay();
    adsrParams.sustain = adsrSettings.getSustain();
    adsrParams.release = adsrSettings.getRelease();

    setParameters(adsrParams);
}

//����Process�еĸ���ADSR��Ϣ
void ADSRData::voiceUpdate(juce::AudioProcessorValueTreeState& apvts)
{
    getParamValue(apvts);
    updateADSR();
}
