

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "Data/OscData.h"
#include "Data/ADSRData.h"
#include "Data/FilterData.h"
#include "Data/WaveshaperData.h"
#include "Data/ReverbData.h"
#include "Data/GainData.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound(juce::SynthesiserSound*) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;    
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
    void voiceUpdateAllModulators(juce::AudioProcessorValueTreeState& apvts, double sampleRate);

    OscData& getOscillator1() { return osc1; }
    OscData& getOscillator2() { return osc2; }
    ADSRData& getADSR() { return adsr; }
    FilterData& getFilter() { return filter; }
    GainData& getGain() { return gain; }

private:
    static constexpr int numChannelsToProcess{ 2 };
    juce::AudioBuffer<float> synthBuffer;
    OscData osc1;
    OscData osc2;
    FilterData filter;
    WaveshaperData distortion;

    ADSRData adsr;
    GainData gain;
    bool isPrepared{ false };
};