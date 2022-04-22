
#include "ChorusData.h"

void ChorusData::prepare(const juce::dsp::ProcessSpec& spec)
{
    chorus.prepare(spec);
    isPrepared = true;
}

void ChorusData::setChorusParameters(const float rate, const float depth, const float centerDelay,
    const float fdbk, const float mix)
{
    chorus.setRate(rate);
    chorus.setDepth(depth);
    chorus.setCentreDelay(centerDelay);
    chorus.setFeedback(fdbk);
    chorus.setMix(mix);
}

void ChorusData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);
    juce::dsp::AudioBlock<float> block(buffer);
    chorus.process(juce::dsp::ProcessContextReplacing<float>(block));
}

void ChorusData::reset()
{
    chorus.reset();
}

void ChorusData::createParamLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout)
{
    layout.add(std::make_unique<juce::AudioParameterFloat>("CHORUSRATE", "Chorus Rate",
        juce::NormalisableRange<float>{0.0f, 99.0f, 0.01f, 0.5f }, 1.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("CHORUSDEPTH", "Chorus Depth",
        juce::NormalisableRange<float>{0.0f, 1.0f, 0.1f }, 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("CHORUSCENTERDELAY", "Chorus Center Delay",
        juce::NormalisableRange<float>{1.0f, 100.0f, 0.1f}, 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("CHORUSFEEDBACK", "Chorus Feedback",
        juce::NormalisableRange<float>{-1.0f, 1.0f, 0.1f }, 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("CHORUSMIX", "Chorus Mix",
        juce::NormalisableRange<float>{0.0f, 1.0f, 0.1f }, 0.0f));
}
