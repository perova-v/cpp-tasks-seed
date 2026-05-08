#include <vector>
#include <cstdint>
#include <string>
#include <stdexcept>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <array>
#include <limits>

#include "base85ed.h"


namespace
{

const char B85_ALPHABET[] =
    "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%&()*+-;<=>?@^_`{|}~";

std::array<int, 256> make_decode_table()
{
    std::array<int, 256> table;
    table.fill(-1);

    for (int i = 0; i < 85; ++i)
    {
        table[static_cast<unsigned char>(B85_ALPHABET[i])] = i;
    }

    return table;
}

const std::array<int, 256> &decode_table()
{
    static const std::array<int, 256> table = make_decode_table();
    return table;
}

void append_encoded_uint32(std::vector<uint8_t> &out, uint32_t value, size_t count)
{
    uint8_t encoded[5];

    for (int i = 4; i >= 0; --i)
    {
        encoded[i] = static_cast<uint8_t>(B85_ALPHABET[value % 85]);
        value /= 85;
    }

    out.insert(out.end(), encoded, encoded + count);
}

} // namespace


std::vector<uint8_t> base85::encode(std::vector<uint8_t> const &bytes)
{
    std::vector<uint8_t> out;
    out.reserve(((bytes.size() + 3) / 4) * 5);

    for (size_t i = 0; i < bytes.size(); i += 4)
    {
        size_t chunk_size = bytes.size() - i;
        if (chunk_size > 4) chunk_size = 4;

        uint32_t value = 0;
        for (size_t j = 0; j < 4; ++j)
        {
            value <<= 8;
            if (j < chunk_size)
            {
                value |= bytes[i + j];
            }
        }

        append_encoded_uint32(out, value, chunk_size == 4 ? 5 : chunk_size + 1);
    }

    return out;
}


std::vector<uint8_t> base85::decode(std::vector<uint8_t> const &b85str)
{
    const auto &table = decode_table();
    size_t padding = (5 - b85str.size() % 5) % 5;
    size_t full_size = b85str.size() + padding;

    std::vector<uint8_t> out;
    out.reserve((full_size / 5) * 4);

    for (size_t i = 0; i < full_size; i += 5)
    {
        uint64_t value = 0;

        for (size_t j = 0; j < 5; ++j)
        {
            uint8_t c = (i + j < b85str.size()) ? b85str[i + j] : static_cast<uint8_t>('~');
            int decoded = table[c];
            if (decoded < 0)
            {
                throw std::invalid_argument("bad base85 character at position " + std::to_string(i + j));
            }

            value = value * 85 + static_cast<uint64_t>(decoded);
        }

        if (value > std::numeric_limits<uint32_t>::max())
        {
            throw std::invalid_argument("base85 overflow in hunk starting at byte " + std::to_string(i));
        }

        uint32_t v32 = static_cast<uint32_t>(value);
        out.push_back(static_cast<uint8_t>((v32 >> 24) & 0xff));
        out.push_back(static_cast<uint8_t>((v32 >> 16) & 0xff));
        out.push_back(static_cast<uint8_t>((v32 >> 8) & 0xff));
        out.push_back(static_cast<uint8_t>(v32 & 0xff));
    }

    if (padding > 0)
    {
        out.resize(out.size() - padding);
    }

    return out;
}
