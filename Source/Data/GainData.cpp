

#include "GainData.h"
void GainData::prepare(const juce::dsp::ProcessSpec& spec)
{
    gain.prepare(spec);
    isPrepared = true;
}


void GainData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);
    juce::dsp::AudioBlock<float> block(buffer);
    gain.process(juce::dsp::ProcessContextReplacing<float>(block));
}

void GainData::reset()
{
    gain.reset();
}

void GainData::createParamLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout)
{
    layout.add(std::make_unique<juce::AudioParameterFloat>("GAIN", "Gain",
        juce::NormalisableRange<float>{-48.0f, 0.0f, 0.1f}, -12.0f));
}

void GainData::getParamValue(juce::AudioProcessorValueTreeState& apvts)
{
    gainVal = apvts.getRawParameterValue("GAIN")->load();
}

void GainData::voiceUpdate(juce::AudioProcessorValueTreeState& apvts)
{
    getParamValue(apvts);
    gain.setGainDecibels(gainVal);

}
