

#include "ReverbData.h"

void ReverbData::prepare(const juce::dsp::ProcessSpec& spec)
{
    reverb.prepare(spec);
    isPrepared = true;
}

void ReverbData::updateReverb(const float roomSize, const float damping, const float wetLevel,
    const float dryLevel, const float width, const float freezeMode)
{
    reverbParameters.roomSize = roomSize;
    reverbParameters.damping = damping;
    reverbParameters.wetLevel = wetLevel;
    reverbParameters.dryLevel = dryLevel;
    reverbParameters.width = width;
    reverbParameters.freezeMode = freezeMode;

    reverb.setParameters(reverbParameters);
}

void ReverbData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);
    juce::dsp::AudioBlock<float> block(buffer);
    reverb.process(juce::dsp::ProcessContextReplacing<float>(block));
}

void ReverbData::reset()
{
    reverb.reset();
}

void ReverbData::createParamLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout)
{
    layout.add(std::make_unique<juce::AudioParameterFloat>("REVERBROOM", "Reverb Room",
        juce::NormalisableRange<float>{0.0f, 1.0f, 0.1f }, 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("REVERBDAMP", "Reverb Damp",
        juce::NormalisableRange<float>{0.0f, 1.0f, 0.1f }, 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("REVERBWET", "Reverb Wet",
        juce::NormalisableRange<float>{0.0f, 1.0f, 0.1f }, 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("REVERBDRY", "Reverb Dry",
        juce::NormalisableRange<float>{0.0f, 1.0f, 0.1f }, 1.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("REVERBWIDTH", "Reverb Width",
        juce::NormalisableRange<float>{0.0f, 1.0f, 0.1f }, 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("REVERBFREEZE", "Reverb Freeze",
        juce::NormalisableRange<float>{0.0f, 1.0f, 0.1f }, 0.0f));
}
