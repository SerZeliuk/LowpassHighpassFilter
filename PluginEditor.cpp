/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LowHighpassFilterAudioProcessorEditor::
LowHighpassFilterAudioProcessorEditor(
    LowHighpassFilterAudioProcessor& p,
    juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor(&p), audioProcessor(p) {
    addAndMakeVisible(cutoffFrequencySlider);

    //cutoffFrequencySlider.setSliderStyle(
    //    juce::Slider::SliderStyle::LinearVertical);
    cutoffFrequencySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    cutoffFrequencyAttachment.reset(
        new juce::AudioProcessorValueTreeState::SliderAttachment(
            vts, "cutoff_frequency", cutoffFrequencySlider));

    addAndMakeVisible(cutoffFrequencyLabel);
    cutoffFrequencyLabel.setText("Cutoff Frequency",
        juce::dontSendNotification);

    addAndMakeVisible(highpassButton);
    highpassAttachment.reset(
        new juce::AudioProcessorValueTreeState::
        ButtonAttachment(vts, "highpass", highpassButton));

    addAndMakeVisible(highpassButtonLabel);
    highpassButtonLabel.setText("Highpass", juce::dontSendNotification);

    setSize(200, 400);
}

LowHighpassFilterAudioProcessorEditor::~LowHighpassFilterAudioProcessorEditor()
{
}

//==============================================================================
void LowHighpassFilterAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.fillAll(juce::Colours::palegoldenrod);
    g.setColour (juce::Colours::crimson);
    g.setFont (15.0f);
    g.drawFittedText ("Cudowny filtr, 10/10", getLocalBounds(), juce::Justification::bottomLeft, 0.5f);
}

void LowHighpassFilterAudioProcessorEditor::resized() {
    cutoffFrequencySlider.setBounds({ 15, 35, 100, 300 });
    cutoffFrequencyLabel.setBounds({ cutoffFrequencySlider.getX() + 30,
                                    cutoffFrequencySlider.getY() - 30,
                                    200, 50 });
    highpassButton.setBounds(
        { cutoffFrequencySlider.getX(),
         cutoffFrequencySlider.getY() +
          cutoffFrequencySlider.getHeight() + 15,
         30, 50 });
    highpassButtonLabel.setBounds(
        { cutoffFrequencySlider.getX() + highpassButton.getWidth() + 15,
         highpassButton.getY(),
         cutoffFrequencySlider.getWidth() - highpassButton.getWidth(),
         highpassButton.getHeight() });
}
