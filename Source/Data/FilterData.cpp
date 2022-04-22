

#include "FilterData.h"

void FilterData::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    juce::dsp::ProcessSpec spec;

    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = outputChannels;

    filter.prepare(spec);
    isPrepared = true;
}

void FilterData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);
    juce::dsp::AudioBlock<float> block(buffer);
    filter.process(juce::dsp::ProcessContextReplacing<float>(block));
}

//void FilterData::updateFilterParameters(const int filterType, const float frequency, const float resonance,
//    const float modulator)
//{
//    switch (filterType)
//    {
//        case 0:
//            filter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
//            break;
//
//        case 1:
//            filter.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
//            break;
//
//        case 2:
//            filter.setType(juce::dsp::StateVariableTPTFilterType::highpass);
//            break;
//
//        default:
//            jassertfalse;
//            break;
//    }
//
//    float modulatedFrequency = frequency * modulator;
//    modulatedFrequency = std::fmax(std::fmin(modulatedFrequency, 20000.0f), 20.0f);
//
//    filter.setCutoffFrequency(modulatedFrequency);
//    filter.setResonance(resonance);
//}



void FilterData::resetFilter()
{
    filter.reset();
}

void FilterData::createParamLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout)
{
    layout.add(std::make_unique<juce::AudioParameterFloat>("LowCutFreq", "LowCutFreq", juce::NormalisableRange<float>(20.f, 2000.f, 1.f, 1.f), 20.f));

    layout.add(std::make_unique<juce::AudioParameterFloat>("HighCutFreq", "HighCutFreq", juce::NormalisableRange<float>(20.f, 2000.f, 1.f, 1.f), 2000.f));

    layout.add(std::make_unique<juce::AudioParameterFloat>("PeakFreq", "PeakFreq", juce::NormalisableRange<float>(20.f, 2000.f, 1.f, 1.f), 750.f));

    layout.add(std::make_unique<juce::AudioParameterFloat>("PeakGain", "PeakGain", juce::NormalisableRange<float>(-24.f, 24.f, 0.5f, 1.f), 0.0f));

    layout.add(std::make_unique<juce::AudioParameterFloat>("PeakQuality", "PeakQuality", juce::NormalisableRange<float>(0.1f, 10.f, 0.05f, 1.f), 1.f));

    juce::StringArray stringArray;
    for (int i = 0; i < 4; i++)
    {
        juce::String str;
        str << (12 + i * 12);
        str << "db/Oct";
        stringArray.add(str);
    }

    layout.add(std::make_unique<juce::AudioParameterChoice>("LowCutSlope", "LowCutSlope", stringArray, 0));

    layout.add(std::make_unique<juce::AudioParameterChoice>("HighCutSlope", "HighCutSlope", stringArray, 0));
}

void FilterData::getParamValue(juce::AudioProcessorValueTreeState& apvts)
{
    filterSettings.setLowCutFreq(apvts.getRawParameterValue("LowCutFreq")->load());

    filterSettings.setHighCutFreq(apvts.getRawParameterValue("HighCutFreq")->load());

    filterSettings.setPeakFreq(apvts.getRawParameterValue("PeakFreq")->load());

    filterSettings.setPeakGain(apvts.getRawParameterValue("PeakGain")->load());

    filterSettings.setPeakQuality(apvts.getRawParameterValue("PeakQuality")->load());

    filterSettings.setLowCutSlope(static_cast<Slope>(apvts.getRawParameterValue("LowCutSlope")->load()));

    filterSettings.setHighCutSlope(static_cast<Slope>(apvts.getRawParameterValue("HighCutSlope")->load()));
}

void FilterData::voiceUpdate(juce::AudioProcessorValueTreeState& apvts, double sampleRate)
{
    getParamValue(apvts);
    setSampleRate(sampleRate);
    updatePeakFilter(filterSettings);
    updateLowCutFilter(filterSettings);
    updateHighCutFilter(filterSettings);
}

void FilterData::updatePeakFilter(FilterSettings& filterSettings)
{
    auto peakCoefficients = juce::dsp::IIR::Coefficients<float>::makePeakFilter(sr, filterSettings.getPeakFreq(), filterSettings.getPeakQuality(), juce::Decibels::decibelsToGain(filterSettings.getPeakGain()));

    updateCoefficients(leftChain.get<ChainPosition::Peak>().coefficients, peakCoefficients);

    updateCoefficients(rightChain.get<ChainPosition::Peak>().coefficients, peakCoefficients);
}

void FilterData::updateCoefficients(Coefficients& old, const Coefficients& replacements)
{
    *old = *replacements;

}

void FilterData::updateLowCutFilter(FilterSettings& filterSettings)
{
    auto cutCoefficients = juce::dsp::FilterDesign<float>::designIIRHighpassHighOrderButterworthMethod(filterSettings.getLowCutFreq(), sr, 2 * (filterSettings.getLowCutSlope() + 1));

    //Left
    auto& leftLowCut = leftChain.get<ChainPosition::LowCut>();
    updateCutFilter(leftLowCut, cutCoefficients, filterSettings.getLowCutSlope());

    ////Right
    auto& rightLowCut = rightChain.get<ChainPosition::LowCut>();
    updateCutFilter(rightLowCut, cutCoefficients, filterSettings.getLowCutSlope());
}

void FilterData::updateHighCutFilter(FilterSettings& filterSettings)
{
    auto highCutCoefficients = juce::dsp::FilterDesign<float>::designIIRLowpassHighOrderButterworthMethod(filterSettings.getHighCutFreq(), sr, 2 * (filterSettings.getHighCutSlope() + 1));

    auto& leftHighCut = leftChain.get<ChainPosition::HighCut>();
    updateCutFilter(leftHighCut, highCutCoefficients, filterSettings.getHighCutSlope());

    auto& rightHighCut = rightChain.get<ChainPosition::HighCut>();
    updateCutFilter(rightHighCut, highCutCoefficients, filterSettings.getHighCutSlope());
}

void FilterData::setSampleRate(double sampleRate)
{
    sr = sampleRate;
}
