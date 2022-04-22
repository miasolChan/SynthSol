

#include "PhaserData.h"

void PhaserData::prepare(const juce::dsp::ProcessSpec& spec)
{
    phaser.prepare(spec);
    isPrepared = true;
}

void PhaserData::setPhaserParameters(const float rate, const float depth, const float centerFreq,
    const float fdbk, const float mix)
{
    phaser.setRate(rate);
    phaser.setDepth(depth);
    phaser.setCentreFrequency(centerFreq);
    phaser.setFeedback(fdbk);
    phaser.setMix(mix);
}

void PhaserData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);
    juce::dsp::AudioBlock<float> block(buffer);
    phaser.process(juce::dsp::ProcessContextReplacing<float>(block));
}

void PhaserData::reset()
{
    phaser.reset();
}

void PhaserData::createParamLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout)
{
    layout.add(std::make_unique<juce::AudioParameterFloat>("PHASERRATE", "Phaser Rate",
        juce::NormalisableRange<float>{0.0f, 50.0f, 0.01f, 0.6f }, 1.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("PHASERDEPTH", "Phaser Depth",
        juce::NormalisableRange<float>{0.0f, 1.0f, 0.1f }, 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("PHASERCENTERFREQ", "Phaser Center Frequency",
        juce::NormalisableRange<float>{20.0f, 20000.0f, 0.1f, 0.6f }, 500.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("PHASERFEEDBACK", "Phaser Feedback",
        juce::NormalisableRange<float>{-1.0f, 1.0f, 0.1f }, 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("PHASERMIX", "Phaser Mix",
        juce::NormalisableRange<float>{0.0f, 1.0f, 0.1f }, 0.0f));
}
