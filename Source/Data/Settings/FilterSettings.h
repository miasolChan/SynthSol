

#pragma once
enum Slope
{
    Slope_12,
    Slope_24,
    Slope_36,
    Slope_48
};

class FilterSettings
{
public:
    FilterSettings() {};
    ~FilterSettings() {};

    float getPeakFreq() { return peakFreq; };
    float getPeakGain() { return peakGainInDecibels; };
    float getPeakQuality() { return peakQuality; };
    float getLowCutFreq() { return lowCutFreq; };
    float getHighCutFreq() { return highCutFreq; };
    Slope getLowCutSlope() { return lowCutSlope; };
    Slope getHighCutSlope() { return highCutSlope; };

    void setPeakFreq(float pf) { peakFreq = pf; };
    void setPeakGain(float pg) { peakGainInDecibels = pg; };
    void setPeakQuality(float pq) { peakQuality = pq; };
    void setLowCutFreq(float lcf) { lowCutFreq = lcf; };
    void setHighCutFreq(float hcf) { highCutFreq = hcf; };
    void setLowCutSlope(Slope lcs) { lowCutSlope = lcs; };
    void setHighCutSlope(Slope hcs) { highCutSlope = hcs; };
private:
    float peakFreq{ 0 };
    float peakGainInDecibels{ 0 }; 
    float peakQuality{ 1.f };
    float lowCutFreq{ 0 }; 
    float highCutFreq{ 0 };
    Slope lowCutSlope{ Slope::Slope_12 };
    Slope highCutSlope{ Slope::Slope_12 };

};
