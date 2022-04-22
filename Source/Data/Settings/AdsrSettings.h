/*
  ==============================================================================

    AdsrSettings.h
    Created: 20 Apr 2022 4:02:15pm
    Author:  Miasol

  ==============================================================================
*/

#pragma once
class AdsrSettings
{
public:
    AdsrSettings() {};
    ~AdsrSettings() {};
    void setAttack(float at) { attack = at; };
    void setDecay(float de) { decay = de; };
    void setSustain(float su) { sustain = su; };
    void setRelease(float re) { release = re; };

    float getAttack() { return attack; };
    float getDecay() { return decay; };
    float getSustain() { return sustain; };
    float getRelease() { return release; };
private:
    float attack;
    float decay;
    float sustain;
    float release;
};
