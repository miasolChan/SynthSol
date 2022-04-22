
#pragma once
#include <JuceHeader.h>
#include "Settings/FilterSettings.h"
class FilterData
{
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);

    void process(juce::AudioBuffer<float>& buffer);
    //void updateFilterParameters(const int filterType, const float frequency, const float resonance,const float modulator);
    //
    
    void resetFilter();
    //设置layout
    void createParamLayout(juce::AudioProcessorValueTreeState::ParameterLayout& layout);
    //获取APVTS
    void getParamValue(juce::AudioProcessorValueTreeState& apvts);
    //更新filter
    void voiceUpdate(juce::AudioProcessorValueTreeState& apvts, double sampleRate);
private:
    FilterSettings filterSettings;
    juce::dsp::StateVariableTPTFilter <float> filter;
    bool isPrepared{ false };

    using Filter = juce::dsp::IIR::Filter<float>;

    using CutFilter = juce::dsp::ProcessorChain<Filter, Filter, Filter, Filter>;

    using MonoChain = juce::dsp::ProcessorChain<CutFilter, Filter, CutFilter>;

    MonoChain leftChain, rightChain;

    enum ChainPosition
    {
        LowCut,
        Peak,
        HighCut
    };

    void updatePeakFilter(FilterSettings& filterSettings);

    using Coefficients = Filter::CoefficientsPtr;

    static void updateCoefficients(Coefficients& old, const Coefficients& replacements);

    template<int index, typename ChainType, typename CoefficientTypes>
    void update(ChainType& chain, const CoefficientTypes& coefficients)
    {
        updateCoefficients(chain.template get<index>().coefficients, coefficients[index]);
        chain.template setBypassed<index>(false);
    }

    template<typename ChainType, typename CoefficientTypes>
    void updateCutFilter(ChainType& leftLowCut, const CoefficientTypes& cutCoefficients, const Slope& lowCutSlope)
    {
        leftLowCut.template setBypassed<0>(true);
        leftLowCut.template setBypassed<1>(true);
        leftLowCut.template setBypassed<2>(true);
        leftLowCut.template setBypassed<3>(true);

        //switch (chainSettings.lowCutSlope)
        switch (lowCutSlope)
        {
        case Slope_48:
        {
            update<3>(leftLowCut, cutCoefficients);
        }
        case Slope_36:
        {
            update<2>(leftLowCut, cutCoefficients);
        }
        case Slope_24:
        {
            update<1>(leftLowCut, cutCoefficients);
        }
        case Slope_12:
        {
            update<0>(leftLowCut, cutCoefficients);
        }

        }
    }

    void updateLowCutFilter(FilterSettings& filterSettings);

    void updateHighCutFilter(FilterSettings& filterSettings);

    void setSampleRate(double sampleRate);

    double sr;
    
};