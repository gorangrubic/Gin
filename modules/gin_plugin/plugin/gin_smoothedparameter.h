#pragma once

class Processor;
//==============================================================================
/** A silky smooth parameter
*/
template <class T>
class SmoothedParameter : public gin::Parameter
{
public:
    SmoothedParameter (Processor& p, String uid_, String name_, String shortName_, String label_,
                       float minValue_, float maxValue_,
                       float intervalValue_, float defaultValue_, float skewFactor_ = 1.0f,
                       std::function<String (const gin::Parameter&, float)> textFunction_ = nullptr)
        : Parameter (p, uid_, name_, shortName_, label_, minValue_, maxValue_, intervalValue_, defaultValue_, skewFactor_, textFunction_)
    {
        smoother.setValue (range.convertTo0to1 (value));
    }

    SmoothedParameter (Processor& p, String uid_, String name_, String shortName_, String label_,
                       NormalisableRange<float> range_, float defaultValue_,
                       std::function<String (const gin::Parameter&, float)> textFunction_ = nullptr)
        : Parameter (p, uid_, name_, shortName_, label_, range_, defaultValue_, textFunction_)
    {
        smoother.setValue (range.convertTo0to1 (value));
    }
    
    void prepareToPlay (double sampleRate, int /*samplesPerBlock*/) override
    {
        smoother.setSampleRate (sampleRate);
    }
    
    void reset() override
    {
        smoother.snapToValue();
    }
    
    //==============================================================================
    void setUserValue (float v) override
    {
        v = jlimit(range.start, range.end, range.snapToLegalValue (v));
        if (! almostEqual (value, v))
        {
            value = v;
            smoother.setValue (range.convertTo0to1 (value));

            triggerAsyncUpdate();
        }
    }
    
    void setUserValueNotifingHost (float v) override
    {
        v = jlimit (range.start, range.end, range.snapToLegalValue (v));
        if (! almostEqual (value, v))
        {
            value = v;
            smoother.setValue (range.convertTo0to1 (value));
            
            setValueNotifyingHost (getValue());

            triggerAsyncUpdate();
        }
    }
    
    void setValue (float valueIn) override
    {
        valueIn = jlimit (0.0f, 1.0f, valueIn);
        float newValue = range.snapToLegalValue (range.convertFrom0to1 (valueIn));

        if (! almostEqual (value, newValue))
        {
            value = newValue;
            smoother.setValue (range.convertTo0to1 (value));
            
            triggerAsyncUpdate();
        }
    }

    //==============================================================================
    float getProcValue (int stepSize) override
    {
        if (smoother.isSmoothing())
        {
            auto v = range.convertFrom0to1 (smoother.getCurrentValue());
            smoother.process (stepSize);
            
            if (conversionFunction != nullptr)
                return conversionFunction (v);
            
            return v;
        }
        return gin::Parameter::getProcValue (stepSize);
    }
    
    void setSmoothingTime (float t)
    {
        smoother.setTime (t);
    }
    
    bool isSmoothingActive() override                   { return smoother.isSmoothing(); }
    
protected:
    T smoother;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SmoothedParameter)
};
