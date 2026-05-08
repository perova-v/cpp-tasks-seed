#include <gtest/gtest.h>

#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <utility>
#include <string.h>

#include "base85ed.h"

const std::vector<std::pair<const char *, const char * >> short_cases =
{
    { "",     ""     },
    { "F#",   "1"    },
    { "F){",  "12"   },
    { "F)}j", "123"  },
    { "F)}kW","1234" }
};

const std::vector<std::pair<const char *, const char * >> string_cases =
{
    { "Xk~0{Zv", "hello" },
    { "NM&qnZ!92pZ*pv8Ap", "Hello, world!" },
    { "LSb`dI5i+?b0BVSbRc43b7eL(E&", "Base85 is not base64." },
    { "FflSSG&MFiI5}ZrV`OD!", "0123456789abcdef" },
    { "RA^-&adl~9Yan8BZ+C7WW^Z^PYISXJb0BYaWpW^NXk{R5VS0HWWN&8",
      "The quick brown fox jumps over the lazy dog" }
};

static std::vector<uint8_t> cstr2v(const char *s)
{
    return std::vector<uint8_t>(
               s,
               s + std::string(s).size()
           );
}

static std::vector<uint8_t> str2v(const std::string &s)
{
    return std::vector<uint8_t>(s.begin(), s.end());
}

// Тесты encode
TEST(Base85ShortsEncode, TrivialShortEncodes)
{
    for (const auto &p : short_cases)
    {
        EXPECT_EQ(base85::encode(cstr2v(p.second)), cstr2v(p.first));
    }
}

// Тесты decode
TEST(Base85ShortsDecode, TrivialShortDecodes)
{
    for (const auto &p : short_cases)
    {
        EXPECT_EQ(base85::decode(cstr2v(p.first)), cstr2v(p.second));
    }
}

TEST(Base85KnownStrings, Encode)
{
    for (const auto &p : string_cases)
    {
        EXPECT_EQ(base85::encode(cstr2v(p.second)), cstr2v(p.first));
    }
}

TEST(Base85KnownStrings, Decode)
{
    for (const auto &p : string_cases)
    {
        EXPECT_EQ(base85::decode(cstr2v(p.first)), cstr2v(p.second));
    }
}

TEST(Base85Binary, KnownBinaryEncodes)
{
    const std::vector<std::pair<std::vector<uint8_t>, const char * >> cases =
    {
        { { 0, 0, 0, 0 }, "00000" },
        { { 0, 0, 0, 1 }, "00001" },
        { { 255, 255, 255, 255 }, "|NsC0" },
        { { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 },
          "009C61O)~M2nh-c3=Iws" },
        { { 0, 1, 2, 3, 250, 251, 252, 253, 254, 255 },
          "009C6`uqI-{{H" }
    };

    for (const auto &p : cases)
    {
        EXPECT_EQ(base85::encode(p.first), cstr2v(p.second));
        EXPECT_EQ(base85::decode(cstr2v(p.second)), p.first);
    }
}

TEST(Base85RoundTrip, PrefixesOfText)
{
    const std::string text =
        "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
        " -- this one is deliberately a bit longer than one block";

    for (size_t len = 0; len <= text.size(); ++len)
    {
        std::vector<uint8_t> part = str2v(text.substr(0, len));
        EXPECT_EQ(base85::decode(base85::encode(part)), part) << "len=" << len;
    }
}

TEST(Base85RoundTrip, AllBytePrefixes)
{
    std::vector<uint8_t> bytes;
    for (int i = 0; i < 256; ++i)
    {
        bytes.push_back(static_cast<uint8_t>(i));
    }

    for (size_t len = 0; len <= bytes.size(); ++len)
    {
        std::vector<uint8_t> part(bytes.begin(), bytes.begin() + len);
        EXPECT_EQ(base85::decode(base85::encode(part)), part) << "len=" << len;
    }
}

TEST(Base85Decode, PaddingLikePython)
{
    EXPECT_EQ(base85::decode(cstr2v("0")), std::vector<uint8_t>{});
    EXPECT_EQ(base85::decode(cstr2v("00")), std::vector<uint8_t>({ 0 }));
    EXPECT_EQ(base85::decode(cstr2v("000")), std::vector<uint8_t>({ 0, 0 }));
    EXPECT_EQ(base85::decode(cstr2v("0000")), std::vector<uint8_t>({ 0, 0, 0 }));
}

TEST(Base85Decode, BadInput)
{
    EXPECT_THROW(base85::decode(cstr2v("0000\n")), std::invalid_argument);
    EXPECT_THROW(base85::decode(cstr2v("~~~~~")), std::invalid_argument);
    EXPECT_THROW(base85::decode(cstr2v("~~~~")), std::invalid_argument);
}
