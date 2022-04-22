

#include <JuceHeader.h>
#include "DistortionComponent.h"

//==============================================================================
DistortionComponent::DistortionComponent(juce::AudioProcessorValueTreeState& apvts, juce::String distortionID)
{
    juce::StringArray waveChoices = { "None", "Creamy", "Cheesy", "Cronchy" };
    distortionType.addItemList(waveChoices, 1);
    addAndMakeVisible(distortionType);

    distortionTypeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, distortionID, distortionType);
    distortionLabel.setText("Distortion Type", juce::NotificationType::dontSendNotification);
    addAndMakeVisible(distortionLabel);

}

DistortionComponent::~DistortionComponent()
{
}

void DistortionComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    
    auto labelSpace = bounds.removeFromTop(25.0f);

    g.setColour(CustomColours::grey);
    g.setFont(20.0f);
    g.drawText("Waveshaper", labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.getX(), bounds.getY(),
        bounds.getWidth() - 20, bounds.getHeight(), 5.0f, 5.0f);
    g.setColour(CustomColours::black);
    g.fillRoundedRectangle(bounds.getX(), bounds.getY(), bounds.getWidth() - 20,
        bounds.getHeight(), 5.0f);
}

void DistortionComponent::resized()
{
    const auto startYPos = 55;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;

    distortionType.setBounds(10, startYPos + 5, 90, 30);
    distortionLabel.setBounds(10, startYPos - labelYOffset, 90, labelHeight);
}
