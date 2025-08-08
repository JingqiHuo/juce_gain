

#pragma once

#include "DemoUtilities.h"
#include "DSPDemos_Common.h"
#include <juce_dsp/juce_dsp.h>
using namespace juce::dsp;

//==============================================================================
struct OverdriveDemoDSP
{
    void prepare(const ProcessSpec& spec)
    {
        sampleRate = spec.sampleRate;

        auto& gainUp = overdrive.get<0>();
        gainUp.setGainDecibels(25);
        gainUp.prepare(spec);

        auto& bias = overdrive.get<1>();
        bias.setBias(0.9f);
        bias.prepare(spec);

        auto& wavShaper = overdrive.get<2>();
        wavShaper.functionToUse = distortionFunction;
        wavShaper.prepare(spec);

        auto& dcFilter = overdrive.get<3>();
        dcFilter.state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, 5.0);
        dcFilter.prepare(spec);

        auto& gainDown = overdrive.get<4>();
        gainDown.setGainDecibels(-10.0f);
        gainDown.prepare(spec);

        overdrive.prepare(spec);
    }
    static float distortionFunction(float x)
    {
        const float threshold = 0.1f;
        const float ratio = 4.0f;
        const float drive = 1.8f;
        const float dryWet = 0.6f;

        float sign = (x >= 0) ? 1.0f : -1.0f;
        float absx = std::abs(x);

        float comp = (absx < threshold) ? absx : threshold + (absx - threshold) / ratio;

        float distorted = std::tanh(comp * drive);

        return dryWet * distorted + (1.0f - dryWet) * x;
    }

    void process(const ProcessContextReplacing<float>& context)
    {
        overdrive.process(context);
    }

    void reset()
    {
        overdrive.reset();
    }

    //==============================================================================
    using GainProcessor = Gain<float>;
    using BiasProcessor = Bias<float>;
    using DriveProcessor = WaveShaper<float>;
    using DCFilter = ProcessorDuplicator<IIR::Filter<float>,
        IIR::Coefficients<float>>;

    ProcessorChain<GainProcessor, BiasProcessor, DriveProcessor, DCFilter, GainProcessor> overdrive;

    double sampleRate = 0.0;
};

