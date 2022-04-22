

#include "CompressorData.h"

void CompressorData::prepare(const juce::dsp::ProcessSpec& spec)
{
    comp.prepare(spec);
    isPrepared = true;
}

void CompressorData::setCompressorParameters(const float threshold, const float ratio,
    const float attack, const float release)
{
    comp.setThreshold(threshold);
    comp.setRatio(ratio);
    comp.setAttack(attack);
    comp.setRelease(release);
}

void CompressorData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);
    juce::dsp::AudioBlock<float> block(buffer);
    comp.process(juce::dsp::ProcessContextReplacing<float>(block));
}

void CompressorData::reset()
{
    comp.reset();
}

void CompressorData::createParamLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout)
{
    layout.add(std::make_unique<juce::AudioParameterFloat>("THRESHOLD", "Threshold",
        juce::NormalisableRange<float>{-24.0f, 0.0f, 0.1f }, 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("RATIO", "Ratio",
        juce::NormalisableRange<float>{1.0f, 50.0f, 0.1f, 0.6f}, 1.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("COMPATTACK", "Comp Attack",
        juce::NormalisableRange<float>{0.0f, 800.0f, 0.1f, 0.5f }, 20.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("COMPRELEASE", "Comp Release",
        juce::NormalisableRange<float>{0.01f, 800.0f, 0.1f, 0.5f}, 10.0f));
}
