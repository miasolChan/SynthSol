

#pragma once
#include <JuceHeader.h>
#include "CustomColours.h"

class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
    //可编辑文本框
    struct CustomLabel : public juce::Label
    {
        static juce::String initialPressedKey;

        juce::TextEditor* createEditorComponent() override
        {
            auto* ed = juce::Label::createEditorComponent();

            ed->setJustification(juce::Justification::centred);
            ed->setColour(juce::TextEditor::backgroundColourId, juce::Colours::transparentWhite);
            ed->setInputRestrictions(5, "0123456789.");
            ed->setIndents(4, 0);

            return ed;
        }

        void editorShown(juce::TextEditor* editor) override
        {
            getParentComponent()->setMouseCursor(juce::MouseCursor::NoCursor);
            editor->clear();
            editor->setText(initialPressedKey);
        }

        void editorAboutToBeHidden(juce::TextEditor* ed) override
        {
            getParentComponent()->setMouseCursor(juce::MouseCursor::NormalCursor);
        }
    };
    CustomLookAndFeel();
    ~CustomLookAndFeel();

    juce::Slider::SliderLayout getSliderLayout(juce::Slider& slider) override;

    void drawRotarySlider(juce::Graphics&, int x, int y, int width, int height,
        float sliderPosProportional, float rotaryStartAngle,
        float rotaryEndAngle, juce::Slider&) override;

    CustomLabel* createSliderTextBox(juce::Slider& slider) override;

    //自定义插入符号
    juce::CaretComponent* createCaretComponent(juce::Component* keyFocusOwner) override;


};