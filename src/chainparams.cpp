// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x80;
        pchMessageStart[1] = 0x41;
        pchMessageStart[2] = 0x85;
        pchMessageStart[3] = 0x22;
        vAlertPubKey = ParseHex("04c3519a3171238043573ca96a9830db782a6b3b4c19cfcb761641d4d55bc1ece0c81bf7ad9c11cd8efce547a2e438a0221c90d6f9c429cc050fd16e3023614ad3");
        vchSyncCheckpointPubKey = ParseHex("04825e65387f404c4ba359bce0fc4e8fd482e72d7382b2a379300ab00ec6a310236a5a456a5d29307c6cfad09afae961550046d666f14127de55a5c1c2bf472de9");
        nDefaultPort = 27200;
        nRPCPort = 27300;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        const char* pszTimestamp = "Life is an EMPTY bottle filled with love.";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1440572400, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1440572400;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 27538;

        hashGenesisBlock = uint256("0x0000b1185bb3be91eaed328732e452374d1a9691fd2e84339abbe27235314e3d");
        if (true && (genesis.GetHash() != hashGenesisBlock))
        {
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            while (genesis.GetHash() > hashTarget)
            {
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    printf("NONCE WRAPPED, incrementing time");
                    ++genesis.nTime;
                }
            }
            cout << "genesis: \n" << genesis.ToString() << endl;
            cout << "genesis.GetHash(): " << genesis.GetHash().ToString() << endl;
            cout << "genesis.hashMerkleRoot: " << genesis.hashMerkleRoot.ToString() << endl;
            cout << "genesis.nTime: " << genesis.nTime << endl;
            cout << "genesis.nNonce: " << genesis.nNonce << endl;
        }


        assert(hashGenesisBlock == uint256("0x0000b1185bb3be91eaed328732e452374d1a9691fd2e84339abbe27235314e3d"));
        assert(genesis.hashMerkleRoot == uint256("0x8c4fe44e101705a528707e544c93920b891970b7d34c8c650a6f7985c2184c76"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(29)(29)(29);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(81);
        base58Prefixes[SECRET_KEY] =     list_of(213);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x05)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x05)(0x88)(0xAD)(0xE4);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        bnProofOfStakeLimit = CBigNum(~uint256(0));
        
        nBasicPoWReward = 1000 * COIN;
        nPoWHalving = 1890; 
        nLaunchTime = genesis.nTime;
        nMinDelay = 1; 

        nCoinbaseMaturity = 200;
        nStakeMinConfirmations = 200;

        nStakeMinAge = 2 * 60 * 60;
        nModifierInterval = 5 * 60; 

        nStakeCoinYearReward = 15 * CENT; 

        nLastPOWBlock = 1000000000; 
        nFirstPoSBlock = 8100; 
        nPoSGranularity = 15;
        nTargetSpacing =  (nPoSGranularity + 1) * 2;

        nMaxMoney = nLastPOWBlock * nBasicPoWReward;

    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x81;
        pchMessageStart[1] = 0x17;
        pchMessageStart[2] = 0x83;
        pchMessageStart[3] = 0x31;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 15);
        vAlertPubKey = ParseHex("0471dc165db490094d35cde15b1f5d755fa6ad6f2b5ed0f340e3f17f57389c3c2af113a8cbcc885bde73305a553b5640c83021128008ddf882e856336269080496");
        nDefaultPort = 27400;
        nRPCPort = 27500;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 105388;
        hashGenesisBlock = uint256("0x0001adc6a02a8136d276d7bfff3b1ca99a0d3ec50eb91cfed7050760ac9a1cb9");
        if (true && (genesis.GetHash() != hashGenesisBlock))
        {
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            while (genesis.GetHash() > hashTarget)
            {
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    printf("NONCE WRAPPED, incrementing time");
                    ++genesis.nTime;
                }
            }
            cout << "genesis: \n" << genesis.ToString() << endl;
            cout << "genesis.GetHash(): " << genesis.GetHash().ToString() << endl;
            cout << "genesis.hashMerkleRoot: " << genesis.hashMerkleRoot.ToString() << endl;
            cout << "genesis.nTime: " << genesis.nTime << endl;
            cout << "genesis.nNonce: " << genesis.nNonce << endl;
        }

        assert(hashGenesisBlock == uint256("0x0001adc6a02a8136d276d7bfff3b1ca99a0d3ec50eb91cfed7050760ac9a1cb9"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(50);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(27);
        base58Prefixes[SECRET_KEY]     = list_of(15);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x05)(0x15)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x05)(0x35)(0x83)(0x94);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 20);

        nCoinbaseMaturity = 100;
        nStakeMinConfirmations = 100;

        nStakeMinAge = 8 * 60 * 60; // 
        nModifierInterval = 10 * 60; // time to elapse before new modifier is computed

        nStakeCoinYearReward = 15 * CENT; // 5% per year

        nLastPOWBlock = 100000;

        nMaxMoney = 2654314159 * COIN;

    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;
static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}
void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet ) {
        return false;
    }

    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}


