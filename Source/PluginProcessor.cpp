 /*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthSolAudioProcessor::SynthSolAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif 
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    for (int i = 0; i < 5; ++i)
        synth.addVoice(new SynthVoice());

    synth.addSound(new SynthSound());
}

SynthSolAudioProcessor::~SynthSolAudioProcessor()
{

}

//==============================================================================
const juce::String SynthSolAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthSolAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthSolAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthSolAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthSolAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthSolAudioProcessor::getNumPrograms()
{
    return 1;  
}

int SynthSolAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthSolAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SynthSolAudioProcessor::getProgramName (int index)
{
    return {};
}

void SynthSolAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SynthSolAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = getTotalNumOutputChannels();
    reverb.prepare(spec);
    phaser.prepare(spec);
    chorus.prepare(spec);
    comp.prepare(spec);

    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
}

void SynthSolAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthSolAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SynthSolAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {

            voice->voiceUpdateAllModulators(apvts, getSampleRate());

        }
    }

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    
    // Reverb
    reverb.process(buffer);
    auto& reverbSize = *apvts.getRawParameterValue("REVERBROOM");
    auto& reverbDamp = *apvts.getRawParameterValue("REVERBDAMP");
    auto& reverbWet = *apvts.getRawParameterValue("REVERBWET");
    auto& reverbDry = *apvts.getRawParameterValue("REVERBDRY");
    auto& reverbWidth = *apvts.getRawParameterValue("REVERBWIDTH");
    auto& reverbFreeze = *apvts.getRawParameterValue("REVERBFREEZE");
    reverb.updateReverb(reverbSize, reverbDamp, reverbWet, reverbDry, reverbWidth, reverbFreeze);
    
    // Phaser 
    phaser.process(buffer);
    auto& phaserRate = *apvts.getRawParameterValue("PHASERRATE");
    auto& phaserDepth = *apvts.getRawParameterValue("PHASERDEPTH");
    auto& phaserCenterFreq = *apvts.getRawParameterValue("PHASERCENTERFREQ");
    auto& phaserFeedback = *apvts.getRawParameterValue("PHASERFEEDBACK");
    auto& phaserMix = *apvts.getRawParameterValue("PHASERMIX");
    phaser.setPhaserParameters(phaserRate, phaserDepth, phaserCenterFreq,
        phaserFeedback, phaserMix);

    //Chorus 
    chorus.process(buffer);
    auto& chorusRate = *apvts.getRawParameterValue("CHORUSRATE");
    auto& chorusDepth = *apvts.getRawParameterValue("CHORUSDEPTH");
    auto& chorusCenter = *apvts.getRawParameterValue("CHORUSCENTERDELAY");
    auto& chorusFeedback = *apvts.getRawParameterValue("CHORUSFEEDBACK");
    auto& chorusMix = *apvts.getRawParameterValue("CHORUSMIX");
    chorus.setChorusParameters(chorusRate, chorusDepth, chorusCenter,
        chorusFeedback, chorusMix);

    // Compressor
    comp.process(buffer);
    auto& threshold = *apvts.getRawParameterValue("THRESHOLD");
    auto& ratio = *apvts.getRawParameterValue("RATIO");
    auto& attack = *apvts.getRawParameterValue("COMPATTACK");
    auto& release = *apvts.getRawParameterValue("COMPRELEASE");
    comp.setCompressorParameters(threshold, ratio, attack, release);
}

//==============================================================================
bool SynthSolAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SynthSolAudioProcessor::createEditor()
{
    //test UI
    //return new juce::GenericAudioProcessorEditor(*this);

    return new PuzzleMirrorSynthAudioProcessorEditor (*this);
}

//==============================================================================
void SynthSolAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SynthSolAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthSolAudioProcessor();
}


// layout
juce::AudioProcessorValueTreeState::ParameterLayout SynthSolAudioProcessor::createParams()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    paramLayoutManager.createAllParamLayout(layout);
    return layout;

}