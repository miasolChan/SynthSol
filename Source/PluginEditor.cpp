/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
PuzzleMirrorSynthAudioProcessorEditor::PuzzleMirrorSynthAudioProcessorEditor(SynthSolAudioProcessor& p)
    : AudioProcessorEditor(&p),
    audioProcessor(p),
    osc1(audioProcessor.apvts, "OSC1", "OSC1FMFREQUENCY", "OSC1FMDEPTH","OSC1PITCH","OSC1GAIN"),
    osc2(audioProcessor.apvts, "OSC2", "OSC2FMFREQUENCY", "OSC2FMDEPTH", "OSC2PITCH", "OSC2GAIN"),
    adsrComponent("Volume Envelope", audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE"),
    filter(audioProcessor.apvts, "LowCutFreq","HighCutFreq","PeakFreq","PeakGain","PeakQuality","LowCutSlope","HighCutSlope"),
    reverb(audioProcessor.apvts, "REVERBROOM", "REVERBDAMP", "REVERBWET", "REVERBDRY", "REVERBWIDTH", "REVERBFREEZE"),
    phaser(audioProcessor.apvts, "PHASERRATE", "PHASERDEPTH", "PHASERCENTERFREQ", "PHASERFEEDBACK", "PHASERMIX"),
    distortion(audioProcessor.apvts, "DISTORTIONTYPE"),
    chorus(audioProcessor.apvts, "CHORUSRATE", "CHORUSDEPTH", "CHORUSCENTERDELAY", "CHORUSFEEDBACK", "CHORUSMIX"),
    comp(audioProcessor.apvts, "THRESHOLD", "RATIO", "COMPATTACK", "COMPRELEASE"),
    gain(audioProcessor.apvts, "GAIN")
{
    
    setLookAndFeel(&customLook);
    setSize (1280, 660);
    addAndMakeVisible(osc1);
    addAndMakeVisible(osc2);
    addAndMakeVisible(adsrComponent);
    addAndMakeVisible(filter);
    addAndMakeVisible(comp);
    addAndMakeVisible(reverb);
    addAndMakeVisible(phaser);
    addAndMakeVisible(distortion);
    addAndMakeVisible(chorus);
    addAndMakeVisible(gain);
    
}

PuzzleMirrorSynthAudioProcessorEditor::~PuzzleMirrorSynthAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void PuzzleMirrorSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(CustomColours::black);
}

void PuzzleMirrorSynthAudioProcessorEditor::resized()
{
    const auto x = 5;
    const auto y = 35;
    const auto width = 300;
    const auto height = 200;

    osc1.setBounds(x, y, width+100, height);
    osc2.setBounds(x, 240, width+100, height);
    filter.setBounds(x, 440, width, height);

    adsrComponent.setBounds(filter.getRight(), 440, width, height);

    reverb.setBounds(adsrComponent.getRight(), y, width + 400, height);
    phaser.setBounds(adsrComponent.getRight(), 180, width + 380, height);
    comp.setBounds(adsrComponent.getRight(), 325, width + 320, height);
    chorus.setBounds(adsrComponent.getRight(), 470, width + 380, height);

    distortion.setBounds(getWidth() - 200, y, width - 150, height);

    gain.setBounds(getWidth() - 200, 470, width - 180, height);

    
    //logoComponent.setBounds(chorus.getRight() - 200, 440, 200, 200);
}

