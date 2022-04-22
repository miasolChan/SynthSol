

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================


FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String lowCutFreq, juce::String highCutFreq, juce::String peakFreq, juce::String peakGain, juce::String peakQuality, juce::String lowCutSlope, juce::String highCutSlope)
{
    

    //slider
    setNomalSlider(apvts, lowCutFreqSlider, "lowCutFreq", lowCutFreqAttachment,0);
    setNomalSlider(apvts, peakFreqSlider, "highCutFreq", highCutFreqAttachment,0);
    setNomalSlider(apvts, highCutFreqSlider, "peakFreq", peakFreqAttachment,0);

    setNomalSlider(apvts, peakQualitySlider, "peakQuality", peakQualityAttachment,0);

    setNomalSlider(apvts, peakGainSlider, "peakGain", peakGainAttachment, 1);

    //comboBox
    juce::StringArray slopeChoices = { "lowcut", "highcut" };
    highSlopeBox.addItemList(slopeChoices, 1);
    addAndMakeVisible(highSlopeBox);
    highSlopeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, highCutSlope, highSlopeBox);
}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    g.setColour(CustomColours::grey);
    g.setFont(20.0f);
    g.drawText("Filter", labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 5.0f);
    g.setColour(CustomColours::black);
    g.fillRoundedRectangle(bounds.toFloat(), 5.0f);
}

void FilterComponent::resized()
{
    const auto startYPos = 40;
    const auto sliderWidth = 250;
    const auto sliderHeight = 30;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;

    //filterSelector.setBounds(10, startYPos + 5, 90, 30);
    //filterTypeLabel.setBounds(10, startYPos - labelYOffset, 90, labelHeight);

    //filterCutoffSlider.setBounds(filterSelector.getRight(), startYPos, sliderWidth, sliderHeight);
    //filterCutoffLabel.setBounds(filterCutoffSlider.getX(), filterCutoffSlider.getY() - labelYOffset,
    //    filterCutoffSlider.getWidth(), labelHeight);
    //filterResonanceSlider.setBounds(filterCutoffSlider.getRight(), startYPos, sliderWidth, sliderHeight);
    //filterResonanceLabel.setBounds(filterResonanceSlider.getX(), filterResonanceSlider.getY() - labelYOffset,
    //    filterResonanceSlider.getWidth(), labelHeight);
    lowCutFreqSlider.setBounds(10, startYPos + 90, sliderWidth, 30 );
    peakFreqSlider.setBounds(10, startYPos + 110, sliderWidth, 30);
    highCutFreqSlider.setBounds(10, startYPos + 130, sliderWidth, 30);

    peakGainSlider.setBounds(200, startYPos, sliderWidth-100, sliderHeight+80 );
}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
void FilterComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
    juce::String parameterID, std::unique_ptr<Attachment>& sliderAttachment)
{
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    slider.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::black);
    addAndMakeVisible(slider);

    sliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, parameterID, slider);

    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::black);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}

void FilterComponent::setNomalSlider(juce::AudioProcessorValueTreeState& apvts, juce::Slider& slider, juce::String parameterID, std::unique_ptr<Attachment>& sliderAttachment,int type)
{
    //sliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, parameterID, slider);
    switch (type)
    {
        //Ë®Æ½
        case 0:
            slider.setSliderStyle(juce::Slider::LinearHorizontal);
            break;
        //´¹Ö±
        case 1:
            slider.setSliderStyle(juce::Slider::LinearVertical);
            break;
        default:
            break;
    }
    slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(slider);
}
