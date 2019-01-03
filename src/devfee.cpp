#include "devfee.h"
#include "util.h"
#include "main.h"

DevFee::DevFee()
{
   address = CBitcoinAddress("SVLB9Yv3RecYi4PCRUE2AWaYu8i8S2stCN");
   address2 = CBitcoinAddress("SZtfHrwEMtogjKGUY5J19yoeiTae4Rntgr");
}

void DevFee::Create(CMutableTransaction& txNew, const int idxProofOfStake, const int nBlockHeight)
{
    CAmount nReward = GetBlockValue(nBlockHeight);

    int i = txNew.vout.size();
    CAmount nAmount = nReward * fPercentage;

    LogPrint("devfee", "DevFee::Create() vout size: %s, nReward=%d, nAmount=%d\n", i, nReward, nAmount);

    txNew.vout.resize(i + 1);
    txNew.vout[idxProofOfStake].nValue -= nAmount;
    txNew.vout[i].scriptPubKey = GetScriptForDestination(nBlockHeight < 2000 ? address.Get() : address2.Get());
    txNew.vout[i].nValue = nAmount;
}

bool DevFee::Validate(const CBlock& block, const int nBlockHeight)
{
    CAmount nReward = GetBlockValue(nBlockHeight);

    int i = block.vtx[1].vout.size();
    CAmount nExpectedAmount = nReward * fPercentage;

    LogPrint("devfee", "DevFee::Validate() vout size: %s, nReward=%d, nExpectedAmount=%d\n", i, nReward, nExpectedAmount);

    if (block.vtx[1].vout[i - 1].scriptPubKey != GetScriptForDestination(address.Get()) &&
        block.vtx[1].vout[i - 1].scriptPubKey != GetScriptForDestination(address2.Get())) {
        LogPrintf("DevFee::Validate() : ERROR invalid scriptPubKey\n");
        return false;
    }

    if (block.vtx[1].vout[i -1].nValue != nExpectedAmount) {
        LogPrintf("DevFee::Validate() : ERROR invalid amount nExpectedAmount=%d nValue=%d\n", nExpectedAmount, block.vtx[1].vout[i -1].nValue);
        return false;
    }

    return true;
}