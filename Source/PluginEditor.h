/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/ADSRComponent.h"
#include "UI/OscComponent.h"
#include "UI/FilterComponent.h"
#include "UI/DistortionComponent.h"
#include "UI/ReverbComponent.h"
#include "UI/PhaserComponent.h"
#include "UI/ChorusComponent.h"
#include "UI/CompressorComponent.h"
#include "UI/GainComponent.h"
#include "UI/LookAndFeel/CustomLookAndFeel.h"

//==============================================================================
/**
*/
class PuzzleMirrorSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    PuzzleMirrorSynthAudioProcessorEditor (SynthSolAudioProcessor&);
    ~PuzzleMirrorSynthAudioProcessorEditor() override;
    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    std::vector<juce::Image> imageList;
private:
    CustomLookAndFeel customLook;
    SynthSolAudioProcessor& audioProcessor;
    OscComponent osc1;
    OscComponent osc2;

    ADSRComponent adsrComponent;
    FilterComponent filter;
    ReverbComponent reverb;
    PhaserComponent phaser;
    DistortionComponent distortion;
    ChorusComponent chorus;
    CompressorComponent comp;
    GainComponent gain;

    juce::ImageComponent logoComponent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PuzzleMirrorSynthAudioProcessorEditor)
};
