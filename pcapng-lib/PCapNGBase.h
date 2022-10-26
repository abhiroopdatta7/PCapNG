/**
 * @file Base.h
 * @author Abhiroop Datta (abhiroopdatta7@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-04-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __PCAPNGBase_H__
#define __PCAPNGBase_H__

#include "PCapNGBuffer.h"
#include "PCapNGOption.h"
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <list>
#include <ostream>
#include <sys/types.h>

namespace PCapNG
{

enum BLOCK_TYPE
{
    BLOCK_IDB = 0x00000001, ///< Interface Description Block
    BLOCK_SPB = 0x00000003, ///< Simple Packet Block
    BLOCK_NRB = 0x00000004, ///< Name Resolution Block
    BLOCK_ISB = 0x00000005, ///< Interface Statistics Block
    BLOCK_EPB = 0x00000006, ///< Enhanced Packet Block
    BLOCK_DSB = 0x0000000A, ///< Decryption Secrets Block
    BLOCK_SHB = 0x0A0D0D0A, ///< Section Header Block
};

class Block
{
  public:
    Block()
    {
        _type = 0;
    }

    Block(uint32_t blockType)
    {
        _type = blockType;
    }

    void AddCustomOptionBinCopiable(const uint32_t pen, const char *description, const size_t size)
    {
        auto _option = CustomOption(OptionBase::OPTION_CUSTOM, pen, description, size);
        this->appendOption(&_option);
    }
    void AddCustomOptionStringCopiable(const uint32_t pen, ::std::string description)
    {
        auto _option = CustomOption(OptionBase::OPTION_CUSTOM_STR, pen, description);
        this->appendOption(&_option);
    }
    void AddCustomOptionBinNonCopiable(const uint32_t pen, const char *description, const size_t size)
    {
        auto _option = CustomOption(OptionBase::OPTION_CUSTOM_NO_COPY, pen, description, size);
        this->appendOption(&_option);
    }
    void AddCustomOptionStringNonCopiable(const uint32_t pen, ::std::string description)
    {
        auto _option = CustomOption(OptionBase::OPTION_CUSTOM_STR_NO_COPY, pen, description);
        this->appendOption(&_option);
    }

    friend ::std::ostream &operator<<(::std::ostream &ostream, Block &obj)
    {
        obj.serialize();

        // Serialize Options
        Buffer optionsBuffer;
        for (auto option : obj._options)
        {
            optionsBuffer << *option;
        }

        // Add Option Terminator
        if (obj._options.size())
        {
            auto eoo = EndOfOption();
            optionsBuffer << eoo;
        }

        auto optionsLength = optionsBuffer.size();
        auto type = htonl(obj._type);
        auto blockTotalLength = htonl(obj.BlockTotalLength() + optionsLength);

        ostream.write((const char *)&type, sizeof(uint32_t));
        ostream.write((const char *)&blockTotalLength, sizeof(uint32_t));
        ostream.write(obj._value.data(), obj._value.size());
        ostream.write(optionsBuffer.data(), optionsLength);
        ostream.write((const char *)&blockTotalLength, sizeof(uint32_t));
        return ostream;
    }

  protected:
    virtual void appendOption(OptionBase *option)
    {
        _options.push_back(option);
    }

    virtual void serialize() = 0;
    Buffer _value;

  private:
    uint32_t _type;
    ::std::vector<OptionBase *> _options;

    /**
     * @brief Block Total Length (32 bits): an unsigned value giving the total size of this block, in octets. For
     * instance, the length of a block that does not have a body is 12 octets: 4 octets for the Block Type, 4 octets for
     * the initial Block Total Length and 4 octets for the trailing Block Total Length. This value MUST be a multiple
     * of 4.
     *
     */
    inline uint32_t BlockTotalLength()
    {
        uint32_t length = _value.size() + 12;
        return length;
    }
};

/**
 * @brief Simple Packet Block
 * @ref https://www.ietf.org/archive/id/draft-tuexen-opsawg-pcapng-03.html#name-simple-packet-block
 */
class SimplePacket : public Block
{
  public:
    SimplePacket(uint32_t packetLen, char *packet) : Block(BLOCK_SPB)
    {
        _originalPacketLength = packetLen;
        _packetData.append(packet, packetLen);
    }

  protected:
    void serialize() override
    {
        _value << _originalPacketLength;
        _value << _packetData;
    }

  private:
    uint32_t _originalPacketLength;
    Buffer _packetData;
};

} // namespace PCapNG

#endif /* __PCAPNGBase_H__ */