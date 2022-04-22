

#include "OscData.h"

void OscData::prepareToPlay(juce::dsp::ProcessSpec& proc)
{
    prepare(proc);
    fmOscillator.prepare(proc);
}

void OscData::setOscillatorWaveform(const int waveformChoice)
{
    // Sin Wave: std::sin(x); 
    // Saw wave: x / juce::MathConstants<float>::pi;
    // Square wave  x < 0.0f ? -1.0f : 1.0f; 

    switch (waveformChoice)
    {
        case 0:
            // Sin wave
            initialise([](float x) { return std::sin(x); });
            break;

        case 1:
            // Saw wave
            initialise([](float x) { return x / juce::MathConstants<float>::pi; });
            break;

        case 2:
            // Square wave
            initialise([](float x) { return x < 0.0f ? -1.0f : 1.0f; }); 
            break;

        case 3:
            // White noise
            initialise([](float x) { return juce::Random::getSystemRandom().nextFloat() * x - x/2;});
            break;

        default:
            jassertfalse;
            break;
    }
}

void OscData::setOscillatorFrequency(const int midiNoteNumber)
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber) + fmModulator);
    lastMidiNotePressed = midiNoteNumber;
}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block)
{
    processFMOsc(block);
    process(juce::dsp::ProcessContextReplacing<float>(block));
}

void OscData::processFMOsc(juce::dsp::AudioBlock<float>& block)
{
    for (auto channels = 0; channels < block.getNumChannels(); ++channels)
    {
        for (auto samples = 0; samples < block.getNumSamples(); ++samples)
        {
            fmModulator = fmOscillator.processSample(block.getSample(channels, samples)) * fmDepth;
        }
    }
}

void OscData::setFMParameters(const float frequency, const float depth)
{
    fmOscillator.setFrequency(frequency);
    fmDepth = depth;
    auto currentFrequency = juce::MidiMessage::getMidiNoteInHertz(lastMidiNotePressed) + fmModulator;
    setFrequency(currentFrequency >= 0 ? currentFrequency : currentFrequency * -1.0f);
}

void OscData::createParamLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout)
{
    layout.add(std::make_unique<juce::AudioParameterChoice>("OSC1", "Oscillator 1",
        juce::StringArray{ "Sine", "Saw", "Square", "White Noise" }, 0));
    layout.add(std::make_unique<juce::AudioParameterChoice>("OSC2", "Oscillator 2",
        juce::StringArray{ "Sine", "Saw", "Square", "White Noise" }, 0));

    //FM
    layout.add(std::make_unique<juce::AudioParameterFloat>("OSC1FMFREQUENCY", "Osc 1 FM Frequency",
        juce::NormalisableRange<float>{0.0f, 1000.0f, 0.01f, 0.6f}, 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("OSC2FMFREQUENCY", "Osc 2 FM Frequency",
        juce::NormalisableRange<float>{0.0f, 1000.0f, 0.01f, 0.6f}, 0.0f));

    layout.add(std::make_unique<juce::AudioParameterFloat>("OSC1FMDEPTH", "Osc 1 FM Depth",
        juce::NormalisableRange<float>{0.0f, 1000.0f, 0.01f, 0.6f}, 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("OSC2FMDEPTH", "Osc 2 FM Depth",
        juce::NormalisableRange<float>{0.0f, 1000.0f, 0.01f, 0.6f}, 0.0f));
    //
    layout.add(std::make_unique<juce::AudioParameterInt>("OSC1PITCH", "Oscillator 1 Pitch", -48, 48, 0));
    layout.add(std::make_unique<juce::AudioParameterInt>("OSC2PITCH", "Oscillator 1 Pitch", -48, 48, 0));

    layout.add(std::make_unique<juce::AudioParameterFloat>("OSC1GAIN", "Oscillator 1 Gain", juce::NormalisableRange<float> { -40.0f, 0.2f, 0.1f }, 0.1f, "dB"));
    layout.add(std::make_unique<juce::AudioParameterFloat>("OSC2GAIN", "Oscillator 2 Gain", juce::NormalisableRange<float> { -40.0f, 0.2f, 0.1f }, 0.1f, "dB"));

}

void OscData::getParamValue0(juce::AudioProcessorValueTreeState& apvts)
{
    // Osc select
    oscSettings.setWaveformChoice(apvts.getRawParameterValue("OSC1")->load());

    // FM processing
    oscSettings.setFmFrequency(apvts.getRawParameterValue("OSC1FMFREQUENCY")->load());
    oscSettings.setFmDepth(apvts.getRawParameterValue("OSC1FMDEPTH")->load());
    oscSettings.setFmDepth(apvts.getRawParameterValue("OSC1PITCH")->load());
    oscSettings.setFmDepth(apvts.getRawParameterValue("OSC1GAIN")->load());
    
}
void OscData::getParamValue1(juce::AudioProcessorValueTreeState& apvts) 
{
    oscSettings.setWaveformChoice(apvts.getRawParameterValue("OSC2")->load());
    oscSettings.setFmFrequency(apvts.getRawParameterValue("OSC2FMFREQUENCY")->load());
    oscSettings.setFmDepth(apvts.getRawParameterValue("OSC2FMDEPTH")->load());
    oscSettings.setFmDepth(apvts.getRawParameterValue("OSC2PITCH")->load());
    oscSettings.setFmDepth(apvts.getRawParameterValue("OSC2GAIN")->load());
}

void OscData::voiceUpdate(juce::AudioProcessorValueTreeState& apvts,int type)
{
    switch (type)
    {
    case 0:
        getParamValue0(apvts);
        break;
    case 1:
        getParamValue1(apvts);
        break;
    default:
        break;
    }
    
    setOscillatorWaveform(oscSettings.getWaveFormChoice());
    setFMParameters(oscSettings.getFmFrequency(), oscSettings.getFmDepth());
}
