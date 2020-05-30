#pragma once

//==============================================================================
/**
    The GinLookAndFeel. Black background with while text and controls.
    Very minimalist.
*/
class GinLookAndFeel : public LookAndFeel_V4
{
public:
    GinLookAndFeel();

	enum ColourIds
	{
		whiteColourId            = 0x1500000,
		blackColourId            = 0x1500001,
		displayColourId          = 0x1500002,
		backgroundColourId       = 0x1500003,
		groupColourId            = 0x1500004,
		lightGroupColourId       = 0x1500005,
		grey30ColourId           = 0x1500006,
		grey45ColourId           = 0x1500007,
		grey60ColourId           = 0x1500008,
		grey90ColourId           = 0x1500009,
		glass1ColourId           = 0x150000a,
		glass2ColourId           = 0x150000b,
		matte1ColourId           = 0x150000c,
		matte2ColourId           = 0x150000d,
		title1ColourId           = 0x150000e,
		title2ColourId           = 0x150000f,
		accentColourId           = 0x1500010,

		// Obsolete colours
        colourId1                = 0x8700001,
        colourId2                = 0x8700002,
        colourId3                = 0x8700003,
        colourId4                = 0x8700004,
        colourId5                = 0x8700005,
    };
    
    Colour defaultColour (int idx);

    void drawRotarySlider (Graphics&, int x, int y, int width, int height,
                           float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle,
                           Slider&) override;

    void drawLinearSlider (Graphics&, int x, int y, int width, int height,
                           float sliderPos, float minSliderPos, float maxSliderPos,
                           const Slider::SliderStyle, Slider&) override;


    void drawButtonBackground (Graphics&, Button&, const Colour& backgroundColour,
                               bool isMouseOverButton, bool isButtonDown) override;

    void drawButtonText (Graphics&, TextButton&, bool isMouseOverButton, bool isButtonDown) override;

    void drawComboBox (Graphics&, int width, int height, bool isButtonDown,
                       int buttonX, int buttonY, int buttonW, int buttonH,
                       ComboBox&) override;

    void positionComboBoxText (ComboBox&, Label&) override;
    
    void drawTextEditorOutline (Graphics&, int width, int height, TextEditor&) override;

    int getAlertWindowButtonHeight() override    { return 20; }
};
