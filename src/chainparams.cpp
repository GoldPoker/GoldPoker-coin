// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017 The Bitcoin Green developers
// Copyright (c) 2018 The Gpkr developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "bignum.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("0x000007a5e645d8b8dd5ca2decb3b371772978cad4015d47832a41b8085eaa3f3"))
    (296700, uint256("0xe0273ceb254c70e15945d26c532afe781f228302a53abce455c88cff63abdc2f"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1548929499, // * UNIX timestamp of last checkpoint block
    636216,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    0        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256("0x000009f73c6faf5465e1cef3e029ed2a726cdf013163b91b9b4ecb6badd5b556"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1530489601,
    0,
    0};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of
    (0, uint256("0x5f38eb5967ef70b09b8164c98bcde68cf01dcf46435b83f5f66dc0de18196163"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1530489602,
    0,
    0};


static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = genesis.BuildMerkleTree();
    return genesis;
}


static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Gold Poker Genesis Block";
    const CScript genesisOutputScript = CScript() << ParseHex("043e5a5fbfbb2caa5f4b7c8fd24d890d6c244de254d579b5ba629f64c1b48275f59e0e1c834a60f6ffb4aaa022aaa4866434ca729a12465f80618fb2070045cb16") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xb2;
        pchMessageStart[1] = 0xc9;
        pchMessageStart[2] = 0xc3;
        pchMessageStart[3] = 0xd4;
        vAlertPubKey = ParseHex("03c298d5154b172b2f706773bc190002ec419b618bd8e7eabc3285c29102ba22f7");
        nDefaultPort = 33303;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nSubsidyHalvingInterval = 5256000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Gpkr: 2 blocks
        nTargetSpacing = 1 * 33;  // Gpkr: 33 sec
        nMaturity = 10;
        nMasternodeCountDrift = 1;
        nMaxMoneyOut = 33333333 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 100;
        nModifierUpdateBlock = 299333; //fake stake update

        genesis = CreateGenesisBlock(1530489600, 1209697, 0x1e0ffff0, 1, 50 * COIN);

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000007a5e645d8b8dd5ca2decb3b371772978cad4015d47832a41b8085eaa3f3"));
        assert(genesis.hashMerkleRoot == uint256("0xb2de422ca09c5a4de0bd2e37b949feb74b06b7c38dd08e5ac18a6e7290d5c151"));

        // DNS Seeding
        vSeeds.push_back(CDNSSeedData("s1.gold-poker.com", "s1.gold-poker.com"));
        vSeeds.push_back(CDNSSeedData("s2.gold-poker.com", "s2.gold-poker.com"));
        vSeeds.push_back(CDNSSeedData("s3.gold-poker.com", "s3.gold-poker.com"));
        vSeeds.push_back(CDNSSeedData("s4.gold-poker.com", "s4.gold-poker.com"));

        // Gpkr addresses start with 'G'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 38);
        // Gpkr script addresses start with '9'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 20);
        // Gpkr private keys start with '9' or 'A'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 22);
        // Gpkr BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // Gpkr BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // Gpkr BIP44 coin type is '33303'
        //  BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x49)(0x85).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "03c298d5154b172b2f706773bc190002ec419b618bd8e7eabc3285c29102ba22f7";
        strMasternodePoolDummyAddress = "GQQ6cNVNg1R1A2e1AgtY1FPsh3d1wGekr7";
        nStartMasternodePayments = genesis.nTime + 86400; // 24 hours after genesis creation

        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xb2;
        pchMessageStart[1] = 0xc9;
        pchMessageStart[2] = 0xc3;
        pchMessageStart[3] = 0xd4;
        vAlertPubKey = ParseHex("0447f078288cf5024694ad27634232226d9a35f2c0c91c898327b79339d7cb42106118290cc51083ecd16992f4d43e1be0597d7d2b46d39f425dd480ad52fb5024");
        nDefaultPort = 33302;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Gpkr: 1 day
        nTargetSpacing = 2 * 60;  // Gpkr: 1 minute
        nLastPOWBlock = 500;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 1;
        nMaxMoneyOut = 2000000 * COIN;

        genesis = CreateGenesisBlock(1530489601, 2041133, 0x1e0ffff0, 1, 50 * COIN);

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("000007ea763e678e210d93fd00c90602a7cb090053ffabc2a798caa20ce84fd7"));

        vFixedSeeds.clear();
        vSeeds.clear();

        // Testnet Gpkr addresses start with 'n'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 112);
        // Testnet Gpkr script addresses start with '5'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 10);
        // Testnet private keys start with '5' or 'n' (Bitcoin defaults)
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 240);
        // Testnet Gpkr BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet Gpkr BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Testnet Gpkr BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04464cc44e8055970909976649bb6b59c48c4861e6bd8092dccba7ac23bf383c184c7013cd07545d10f2ea6793ff83b68c7dae27eb7eb7b7e4039d413afb0d6cbe";
        strMasternodePoolDummyAddress = "nQQ6cNVNg1R1A2e1AgtY1FPsh3d1wGekr7";
        nStartMasternodePayments = genesis.nTime + 86400; // 24 hours after genesis
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xb2;
        pchMessageStart[1] = 0xc9;
        pchMessageStart[2] = 0xc3;
        pchMessageStart[3] = 0xd4;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Gpkr: 1 day
        nTargetSpacing = 2 * 60;        // Gpkr: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;

        genesis = CreateGenesisBlock(1530489602, 3, 0x207fffff, 1, 50 * COIN);

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 238079;
        assert(hashGenesisBlock == uint256("0x5f38eb5967ef70b09b8164c98bcde68cf01dcf46435b83f5f66dc0de18196163"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 18828;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}