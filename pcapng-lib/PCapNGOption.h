/**
 * @file PCapNGOption.h
 * @author Abhiroop Datta (abhiroopdatta7@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-10-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef __PCAPNG_OPTION_H__
#define __PCAPNG_OPTION_H__

#include "PCapNGBuffer.h"
#include <cstddef>
#include <cstdint>

namespace PCapNG
{

size_t Pad32(size_t val);

class OptionBase
{
  public:
    OptionBase(uint16_t type)
    {
        _type = type;
    }

    virtual void serialize() = 0;

    friend Buffer &operator<<(Buffer &optionBuffer, OptionBase &obj)
    {
        uint8_t pad = 0;
        obj.serialize();
        auto length = obj.OptionLength();

        optionBuffer << obj._type;
        optionBuffer << length;
        optionBuffer << obj._value;
        // PAD
        uint8_t padWith = 0;
        auto padLength = Pad32(length) - length;
        for (auto i = 0; i < padLength; i++)
            optionBuffer << padWith;
        return optionBuffer;
    }

    uint16_t _type;

    enum OPTION_TYPE
    {
        OPTION_END = 0,
        OPTION_COMMENT = 1,
        OPTION_CUSTOM_STR = 2988,
        OPTION_CUSTOM = 2989,
        OPTION_CUSTOM_STR_NO_COPY = 19372,
        OPTION_CUSTOM_NO_COPY = 19373,
    };

  protected:
    Buffer _value;

  private:
    Buffer _optionDetails;
    inline uint16_t OptionLength()
    {
        uint16_t length = _value.size();
        return length;
    }
};

class EndOfOption : public OptionBase
{
  public:
    EndOfOption() : OptionBase(OPTION_END)
    {
    }

    void serialize() override
    {
    }
};

/* Custom Options */
class CustomOption : public OptionBase
{

  public:
    CustomOption(const uint16_t type, const uint32_t pen, ::std::string data) : OptionBase(type)
    {
        _pen = pen;
        data.append(data.c_str(), data.size());
    }

    CustomOption(const uint16_t type, const uint32_t pen, const char *buffer, const size_t size) : OptionBase(type)
    {
        _pen = pen;
        data.append(buffer, size);
    }

    void serialize() override
    {
        _value << _pen;
        _value << data;
    }

  private:
    uint32_t _pen;
    Buffer data;
};

class Option : public OptionBase
{
  public:
    Option(uint16_t tpye, const ::std::string dec) : OptionBase(tpye)
    {
        _optionDetails.append(dec.c_str(), dec.size());
    }

    Option(uint16_t tpye, const char *dec, size_t size) : OptionBase(tpye)
    {
        _optionDetails.append(dec, size);
    }

    void serialize() override
    {
        _value << _optionDetails;
    }

  private:
    Buffer _optionDetails;
};

} // namespace PCapNG

#endif /* __PCAPNG_OPTION_H__ */