// Copyright (c) 2012-2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <key.h>

#include <base58.h>
#include <script/script.h>
#include <uint256.h>
#include <util.h>
#include <utilstrencodings.h>
#include <test/test_bitcoin.h>

#include <string>
#include <vector>

#include <boost/test/unit_test.hpp>

#ifdef BUILD_BTC
static const std::string strSecret1 = "5HxWvvfubhXpYYpS3tJkw6fq9jE9j18THftkZjHHfmFiWtmAbrj";
static const std::string strSecret2 = "5KC4ejrDjv152FGwP386VD1i2NYc5KkfSMyv1nGy1VGDxGHqVY3";
static const std::string strSecret1C = "Kwr371tjA9u2rFSMZjTNun2PXXP3WPZu2afRHTcta6KxEUdm1vEw";
static const std::string strSecret2C = "L3Hq7a8FEQwJkW1M2GNKDW28546Vp5miewcCzSqUD9kCAXrJdS3g";
#ifdef BUILD_BTC
static const std::string addr1 = "1QFqqMUD55ZV3PJEJZtaKCsQmjLT6JkjvJ";
static const std::string addr2 = "1F5y5E5FMc5YzdJtB9hLaUe43GDxEKXENJ";
static const std::string addr1C = "1NoJrossxPBKfCHuJXT4HadJrXRE9Fxiqs";
static const std::string addr2C = "1CRj2HyM1CXWzHAXLQtiGLyggNT9WQqsDs";
#else  // BUILD_EQB
static const std::string addr1 = "EQBFxikJ6kq2CbWYiJ47YqvoAeo3qXmyU35y";
static const std::string addr2 = "EQBQXtEXCiVEHSz6Yxs3FLqeWTfeSDt4QWND";
static const std::string addr1C = "EQBCFdUkTJqeYkJN2m1nn4HgmcgYob1djRx1";
static const std::string addr2C = "EQBNV8Yaff7kZm6tukEAW2Jtc8mHoxxXCA9Q";
#endif // END_BUILD

static const std::string strAddressBad = "1HV9Lc3sNHZxwj4Zk6fB38tEmBryq2cBiF";
#else  // BUILD_EQB
// Data generated by base58_key_test_gen test case in base58_tests.cpp
static const std::string strSecret1 = "5JERFZm3S4J6rJKFjqgD4giHffF34cUsPsJR9EgCZdJvw6JeR9x";
static const std::string strSecret2 = "5K494XZwps2bGyeL71pWid4noiSNA2cfCibrvRWqcHSptqdmpK4";
static const std::string strSecret1C = "Ky4E3HbPjbYUpbRa45r4FGHEZdnx6wc1Rw1sZMN231G93GdqjDU6";
static const std::string strSecret2C = "L2graZvQzFp2HX1mKYciAiBjBBtxNr8PcicsLoChYjazPaiZpS3q";
static const std::string addr1 = "EQBLzqGEfKfJhkXDKBURi6kH3ESRnrK4beCo";
static const std::string addr2 = "EQBWobZkQNK7GfETrzmTttJggUx2fTTphwkN";
static const std::string addr1C = "EQBPg6uq4y23b3HHtJL2tEjqXXiEgjCQ77c4";
static const std::string addr2C = "EQBKrp4353FBCQEcKDBZjLhKTn3KofwNyjHH";

static const std::string strAddressBad = "EQB89ajamdfJiadm7Y6nASLkugnso199jJqo";
#endif // END_BUILD


BOOST_FIXTURE_TEST_SUITE(key_tests, BasicTestingSetup)

BOOST_AUTO_TEST_CASE(key_test1)
{
    // EQB_TODO generate new test data
#ifdef EQB_BREAK_TEST
    BOOST_ERROR("TEST DISABLED!");
#endif
    return;

    CBitcoinSecret bsecret1, bsecret2, bsecret1C, bsecret2C, baddress1;
    //! EQB_TODO: Fix Test -> BOOST_CHECK( bsecret1.SetString (strSecret1));
    //! EQB_TODO: Fix Test -> BOOST_CHECK( bsecret2.SetString (strSecret2));
    //! EQB_TODO: Fix Test -> BOOST_CHECK( bsecret1C.SetString(strSecret1C));
    //! EQB_TODO: Fix Test -> BOOST_CHECK( bsecret2C.SetString(strSecret2C));
    BOOST_CHECK(!baddress1.SetString(strAddressBad));

#ifdef BUILD_BTC
    CKey key1  = bsecret1.GetKey();
    BOOST_CHECK(key1.IsCompressed() == false);
    CKey key2  = bsecret2.GetKey();
    BOOST_CHECK(key2.IsCompressed() == false);
    CKey key1C = bsecret1C.GetKey();
    BOOST_CHECK(key1C.IsCompressed() == true);
    CKey key2C = bsecret2C.GetKey();
    BOOST_CHECK(key2C.IsCompressed() == true);

    CPubKey pubkey1  = key1. GetPubKey();
    CPubKey pubkey2  = key2. GetPubKey();
    CPubKey pubkey1C = key1C.GetPubKey();
    CPubKey pubkey2C = key2C.GetPubKey();

    BOOST_CHECK(key1.VerifyPubKey(pubkey1));
    BOOST_CHECK(!key1.VerifyPubKey(pubkey1C));
    BOOST_CHECK(!key1.VerifyPubKey(pubkey2));
    BOOST_CHECK(!key1.VerifyPubKey(pubkey2C));

    BOOST_CHECK(!key1C.VerifyPubKey(pubkey1));
    BOOST_CHECK(key1C.VerifyPubKey(pubkey1C));
    BOOST_CHECK(!key1C.VerifyPubKey(pubkey2));
    BOOST_CHECK(!key1C.VerifyPubKey(pubkey2C));

    BOOST_CHECK(!key2.VerifyPubKey(pubkey1));
    BOOST_CHECK(!key2.VerifyPubKey(pubkey1C));
    BOOST_CHECK(key2.VerifyPubKey(pubkey2));
    BOOST_CHECK(!key2.VerifyPubKey(pubkey2C));

    BOOST_CHECK(!key2C.VerifyPubKey(pubkey1));
    BOOST_CHECK(!key2C.VerifyPubKey(pubkey1C));
    BOOST_CHECK(!key2C.VerifyPubKey(pubkey2));
    BOOST_CHECK(key2C.VerifyPubKey(pubkey2C));
#else // BUILD_EQB
    //! EQB_TODO: Fix above test prepartion statements 
#endif // END_BUILD
    //! EQB_TODO: Fix Test -> BOOST_CHECK(DecodeDestination(addr1)  == CTxDestination(pubkey1.GetID()));
    //! EQB_TODO: Fix Test -> BOOST_CHECK(DecodeDestination(addr2)  == CTxDestination(pubkey2.GetID()));
    //! EQB_TODO: Fix Test -> BOOST_CHECK(DecodeDestination(addr1C) == CTxDestination(pubkey1C.GetID()));
    //! EQB_TODO: Fix Test -> BOOST_CHECK(DecodeDestination(addr2C) == CTxDestination(pubkey2C.GetID()));

    for (int n=0; n<16; n++)
    {
        std::string strMsg = strprintf("Very secret message %i: 11", n);

#ifdef BUILD_BTC
        uint256 hashMsg = Hash(strMsg.begin(), strMsg.end());
#else  // BUILD_EQB
        uint256 hashMsg = SHA3Hash(strMsg.begin(), strMsg.end());
#endif // END_BUILD

        // normal signatures

        std::vector<unsigned char> sign1, sign2, sign1C, sign2C;
#ifdef BUILD_BTC
        BOOST_CHECK(key1.Sign (hashMsg, sign1));
        BOOST_CHECK(key2.Sign (hashMsg, sign2));
        BOOST_CHECK(key1C.Sign(hashMsg, sign1C));
        BOOST_CHECK(key2C.Sign(hashMsg, sign2C));

        BOOST_CHECK( pubkey1.Verify(hashMsg, sign1));
        BOOST_CHECK(!pubkey1.Verify(hashMsg, sign2));
        BOOST_CHECK( pubkey1.Verify(hashMsg, sign1C));
        BOOST_CHECK(!pubkey1.Verify(hashMsg, sign2C));

        BOOST_CHECK(!pubkey2.Verify(hashMsg, sign1));
        BOOST_CHECK( pubkey2.Verify(hashMsg, sign2));
        BOOST_CHECK(!pubkey2.Verify(hashMsg, sign1C));
        BOOST_CHECK( pubkey2.Verify(hashMsg, sign2C));

        BOOST_CHECK( pubkey1C.Verify(hashMsg, sign1));
        BOOST_CHECK(!pubkey1C.Verify(hashMsg, sign2));
        BOOST_CHECK( pubkey1C.Verify(hashMsg, sign1C));
        BOOST_CHECK(!pubkey1C.Verify(hashMsg, sign2C));

        BOOST_CHECK(!pubkey2C.Verify(hashMsg, sign1));
        BOOST_CHECK( pubkey2C.Verify(hashMsg, sign2));
        BOOST_CHECK(!pubkey2C.Verify(hashMsg, sign1C));
        BOOST_CHECK( pubkey2C.Verify(hashMsg, sign2C));

        // compact signatures (with key recovery)

        std::vector<unsigned char> csign1, csign2, csign1C, csign2C;

        BOOST_CHECK(key1.SignCompact (hashMsg, csign1));
        BOOST_CHECK(key2.SignCompact (hashMsg, csign2));
        BOOST_CHECK(key1C.SignCompact(hashMsg, csign1C));
        BOOST_CHECK(key2C.SignCompact(hashMsg, csign2C));

        CPubKey rkey1, rkey2, rkey1C, rkey2C;

        BOOST_CHECK(rkey1.RecoverCompact (hashMsg, csign1));
        BOOST_CHECK(rkey2.RecoverCompact (hashMsg, csign2));
        BOOST_CHECK(rkey1C.RecoverCompact(hashMsg, csign1C));
        BOOST_CHECK(rkey2C.RecoverCompact(hashMsg, csign2C));

        BOOST_CHECK(rkey1  == pubkey1);
        BOOST_CHECK(rkey2  == pubkey2);
        BOOST_CHECK(rkey1C == pubkey1C);
        BOOST_CHECK(rkey2C == pubkey2C);
#else // BUILD_EQB
//! EQB_TODO: Fix above test prepartion statements 
#endif // END_BUILD
    }

    // test deterministic signing

    std::vector<unsigned char> detsig, detsigc;
    std::string strMsg = "Very deterministic message";
#ifdef BUILD_BTC
    uint256 hashMsg = Hash(strMsg.begin(), strMsg.end());
#else  // BUILD_EQB
    uint256 hashMsg = SHA3Hash(strMsg.begin(), strMsg.end());
#endif // END_BUILD
#ifdef BUILD_BTC
    BOOST_CHECK(key1.Sign(hashMsg, detsig));
    BOOST_CHECK(key1C.Sign(hashMsg, detsigc));
    BOOST_CHECK(detsig == detsigc);
#else // BUILD_EQB
//! EQB_TODO: Fix above test prepartion statements 
#endif // END_BUILD
#ifdef BUILD_BTC
    BOOST_CHECK(detsig == ParseHex("304402205dbbddda71772d95ce91cd2d14b592cfbc1dd0aabd6a394b6c2d377bbe59d31d022014ddda21494a4e221f0824f0b8b924c43fa43c0ad57dccdaa11f81a6bd4582f6"));
    BOOST_CHECK(key2.Sign(hashMsg, detsig));
    BOOST_CHECK(key2C.Sign(hashMsg, detsigc));
    BOOST_CHECK(detsig == detsigc);
    BOOST_CHECK(detsig == ParseHex("3044022052d8a32079c11e79db95af63bb9600c5b04f21a9ca33dc129c2bfa8ac9dc1cd5022061d8ae5e0f6c1a16bde3719c64c2fd70e404b6428ab9a69566962e8771b5944d"));
    BOOST_CHECK(key1.SignCompact(hashMsg, detsig));
    BOOST_CHECK(key1C.SignCompact(hashMsg, detsigc));
    BOOST_CHECK(detsig == ParseHex("1c5dbbddda71772d95ce91cd2d14b592cfbc1dd0aabd6a394b6c2d377bbe59d31d14ddda21494a4e221f0824f0b8b924c43fa43c0ad57dccdaa11f81a6bd4582f6"));
    BOOST_CHECK(detsigc == ParseHex("205dbbddda71772d95ce91cd2d14b592cfbc1dd0aabd6a394b6c2d377bbe59d31d14ddda21494a4e221f0824f0b8b924c43fa43c0ad57dccdaa11f81a6bd4582f6"));
    BOOST_CHECK(key2.SignCompact(hashMsg, detsig));
    BOOST_CHECK(key2C.SignCompact(hashMsg, detsigc));
    BOOST_CHECK(detsig == ParseHex("1c52d8a32079c11e79db95af63bb9600c5b04f21a9ca33dc129c2bfa8ac9dc1cd561d8ae5e0f6c1a16bde3719c64c2fd70e404b6428ab9a69566962e8771b5944d"));
    BOOST_CHECK(detsigc == ParseHex("2052d8a32079c11e79db95af63bb9600c5b04f21a9ca33dc129c2bfa8ac9dc1cd561d8ae5e0f6c1a16bde3719c64c2fd70e404b6428ab9a69566962e8771b5944d"));
#else  // BUILD_EQB
    //! EQB_TODO: Fix Test -> BOOST_CHECK(detsig == ParseHex("304502210095846078fabbfc66224a99bc4330b273910febf01a9149e4fb2535252dd850e702202f167de765a4dcbf52e5b2e22d708929074e0907bcff0b6f9fd28e6ccfc56b3a"));
    //! EQB_TODO: Fix Test -> BOOST_CHECK(key2.Sign(hashMsg, detsig));
    //! EQB_TODO: Fix Test -> BOOST_CHECK(key2C.Sign(hashMsg, detsigc));
    //! EQB_TODO: Fix Test -> BOOST_CHECK(detsig == detsigc);
    //! EQB_TODO: Fix Test -> BOOST_CHECK(detsig == ParseHex("30450221008593bc4093235af7a155ec902d31c1a8068e3d87b524167f4b6a70682418bb7f0220023e84b74ede3937b9d9b1e26f3693b90d49133000883e3d1d00afe99249bd3e"));
    //! EQB_TODO: Fix Test -> BOOST_CHECK(key1.SignCompact(hashMsg, detsig));
    //! EQB_TODO: Fix Test -> BOOST_CHECK(key1C.SignCompact(hashMsg, detsigc));
    //! EQB_TODO: Fix Test -> BOOST_CHECK(detsig == ParseHex("1c95846078fabbfc66224a99bc4330b273910febf01a9149e4fb2535252dd850e72f167de765a4dcbf52e5b2e22d708929074e0907bcff0b6f9fd28e6ccfc56b3a"));
    //! EQB_TODO: Fix Test -> BOOST_CHECK(detsigc == ParseHex("2095846078fabbfc66224a99bc4330b273910febf01a9149e4fb2535252dd850e72f167de765a4dcbf52e5b2e22d708929074e0907bcff0b6f9fd28e6ccfc56b3a"));
    //! EQB_TODO: Fix Test -> BOOST_CHECK(key2.SignCompact(hashMsg, detsig));
    //! EQB_TODO: Fix Test -> BOOST_CHECK(key2C.SignCompact(hashMsg, detsigc));
    //! EQB_TODO: Fix Test -> BOOST_CHECK(detsig == ParseHex("1b8593bc4093235af7a155ec902d31c1a8068e3d87b524167f4b6a70682418bb7f023e84b74ede3937b9d9b1e26f3693b90d49133000883e3d1d00afe99249bd3e"));
    //! EQB_TODO: Fix Test -> BOOST_CHECK(detsigc == ParseHex("1f8593bc4093235af7a155ec902d31c1a8068e3d87b524167f4b6a70682418bb7f023e84b74ede3937b9d9b1e26f3693b90d49133000883e3d1d00afe99249bd3e"));
#endif // END_BUILD
}


BOOST_AUTO_TEST_SUITE_END()
