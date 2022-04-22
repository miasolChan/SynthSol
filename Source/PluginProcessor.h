
#pragma once

#include <JuceHeader.h>

#include "SynthSound.h"
#include "SynthVoice.h"
#include "Data/AdsrData.h"
#include "Data/ReverbData.h"
#include "Data/PhaserData.h"
#include "Data/ChorusData.h"
#include "Data/CompressorData.h"

#include"Synth/Modulators/ModulatorsManger.h"
#include"Synth/Parameters/ParamLayoutManager.h"
//==============================================================================
/**
*/
class SynthSolAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    SynthSolAudioProcessor();
    ~SynthSolAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState apvts{ *this, nullptr, "Parameters", createParams() };

    ParamLayoutManager paramLayoutManager;
    
    

private:
    juce::Synthesiser synth;
    juce::AudioProcessorValueTreeState::ParameterLayout createParams();
    ReverbData reverb;
    PhaserData phaser;
    ChorusData chorus;
    CompressorData comp;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthSolAudioProcessor)
};
