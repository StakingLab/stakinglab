#ifndef DEVFEE_H
#define DEVFEE_H

#include "base58.h"

class DevFee
{
public:
    DevFee();
    void Create(CMutableTransaction& txNew, const int idxProofOfStake, const int nBlockHeight);
    bool Validate(const CBlock& block, const int nBlockHeight);
private:
    CBitcoinAddress address;
    CBitcoinAddress address2;
    const float fPercentage{0.05};
};

#endif // DEVFEE_H
