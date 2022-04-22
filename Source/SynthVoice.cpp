

#include "SynthVoice.h"
#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound) 
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) 
{

    osc1.setOscillatorFrequency(midiNoteNumber);
    osc2.setOscillatorFrequency(midiNoteNumber);

    adsr.noteOn();
}

void SynthVoice::stopNote(float velocity, bool allowTailOff) 
{
    adsr.noteOff();
    if (!allowTailOff || !adsr.isActive())
        clearCurrentNote();
    //std::cout << "Note Off" << std::endl;
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{

}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue) 
{

}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    adsr.setSampleRate(sampleRate);

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    osc1.prepareToPlay(spec);
    osc2.prepareToPlay(spec);
    filter.prepareToPlay(sampleRate, samplesPerBlock, outputChannels);
    distortion.prepare(spec);
  
    gain.prepare(spec);
    isPrepared = true;
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) 
{
    jassert(isPrepared);

    if (!isVoiceActive())
        return;

    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);

    synthBuffer.clear();

    juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };    // audio block is an alias for outputBuffer
    gain.process(synthBuffer);
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());

    osc1.getNextAudioBlock(audioBlock);
    osc2.getNextAudioBlock(audioBlock);

    filter.process(synthBuffer);;
    distortion.process(synthBuffer);


    for (int channels = 0; channels < outputBuffer.getNumChannels(); ++channels)
    {
        outputBuffer.addFrom(channels, startSample, synthBuffer, channels, 0, numSamples);

        if (!adsr.isActive())
            clearCurrentNote();
        
    }
}

void SynthVoice::voiceUpdateAllModulators(juce::AudioProcessorValueTreeState& apvts, double sampleRate)
{
    osc1.voiceUpdate(apvts,0);
    osc2.voiceUpdate(apvts, 1);
    adsr.voiceUpdate(apvts);
    filter.voiceUpdate(apvts, sampleRate);
    distortion.voiceUpdate(apvts);
    gain.voiceUpdate(apvts);
}

