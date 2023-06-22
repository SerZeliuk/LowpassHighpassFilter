#include "LowpassHighpassFilter.h"

void LowpassHighpassFilter::setHighpass(bool highpass) {
	this->highpass = highpass;
}

void LowpassHighpassFilter::setCutoffFrequency(float cutoffFrequency) {
	this->cutoffFrequency = cutoffFrequency;
}

void LowpassHighpassFilter::setSamplingRate(float samplingRate) {
	this->samplingRate = samplingRate;
}

void LowpassHighpassFilter::processBlock(juce::AudioBuffer<float>& buffer,
    juce::MidiBuffer&) {
    constexpr auto PI = 3.14159265359f;
    dnBuffer.resize(buffer.getNumChannels(), 0.f);

    // if we perform highpass filtering, we need to 
    // invert the output of the allpass (multiply it
    // by -1)
    const auto sign = highpass ? -1.f : 1.f;
    const auto tan = std::tan(PI * cutoffFrequency / samplingRate);
    // allpass coefficient is constant while processing 
    // a block of samples
    const auto a1 = (tan - 1.f) / (tan + 1.f);

    // actual processing; each channel separately
    for (auto channel = 0; channel < buffer.getNumChannels(); ++channel) {
        auto channelSamples = buffer.getWritePointer(channel);
        // for each sample in the channel
        for (auto i = 0; i < buffer.getNumSamples(); ++i) {
            const auto inputSample = channelSamples[i];

            // allpass filtering
            const auto allpassFilteredSample = a1 * inputSample +
                dnBuffer[channel];
            dnBuffer[channel] = inputSample - a1 * allpassFilteredSample;

            const auto filterOutput =
                0.5f * (inputSample + sign * allpassFilteredSample);

            // assign to the output
            channelSamples[i] = filterOutput;
        }
    }
}