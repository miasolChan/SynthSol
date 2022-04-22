

#pragma once

#include <JuceHeader.h>
#include"LookAndFeel/Dial.h"
#include"LookAndFeel/NameLabel.h"
#include"LookAndFeel/CustomColours.h"
//==============================================================================
/*
*/
class ReverbComponent  : public juce::Component
{
public:
    ReverbComponent(juce::AudioProcessorValueTreeState& apvts, juce::String reverbRoomID, 
        juce::String reverbDampID, juce::String reverbWetID, juce::String reverbDryID, 
        juce::String reverbWidthID, juce::String reverbFreezeID);
    ~ReverbComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
        juce::String parameterID, std::unique_ptr<Attachment>& sliderAttachment, juce::String text);

    Dial roomSizeSlider;
    Dial dampingSlider;
    Dial wetSlider;
    Dial drySlider;
    Dial widthSlider;
    Dial freezeSlider;
    NameLabel roomSizeLabel;
    NameLabel dampingLabel;
    NameLabel wetLabel;
    NameLabel dryLabel;
    NameLabel widthLabel;
    NameLabel freezeLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> roomSizeSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dampingSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> wetSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> drySliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> widthSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> freezeSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbComponent)
};
