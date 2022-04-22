

#pragma once
#include <JuceHeader.h>
#include"Settings/OscSettings.h"
class OscData : public juce::dsp::Oscillator<float>
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& proc);
    void setOscillatorWaveform(const int waveformChoice);
    void setOscillatorFrequency(const int midiNoteNumber);
    void getNextAudioBlock(juce::dsp::AudioBlock<float>& block);
    void processFMOsc(juce::dsp::AudioBlock<float>& block);
    void setFMParameters(const float frequency, const float depth);

    //设置OSC layout
    void createParamLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout);
    //获取APVTS
    void getParamValue0(juce::AudioProcessorValueTreeState& apvts);
    void getParamValue1(juce::AudioProcessorValueTreeState& apvts);
    //用于Process中的更新OSC信息
    void voiceUpdate(juce::AudioProcessorValueTreeState& apvts,int type);

private:
    OscSettings oscSettings;
    juce::dsp::Oscillator<float> fmOscillator{ [](float x) { return std::sin(x); } };
    int lastMidiNotePressed { 0 };
    float fmModulator { 0.0f };
    float fmDepth { 0.0f };
};