

#pragma once

class OscSettings
{
public:
    OscSettings() {};
    ~OscSettings() {};
    void setWaveformChoice(int wfc) { waveformChoice = wfc; };
    void setFmFrequency(float fmF) { fmFrequency = fmF; };
    void setFmDepth(float fmD) { fmDepth = fmD; };

    int getWaveFormChoice() { return waveformChoice; };
    float getFmFrequency() { return fmFrequency; };
    float getFmDepth() { return fmDepth; };

private:
    int waveformChoice;
    float fmFrequency;
    float fmDepth;
};
