/**
 * @file PCapNGBuffer.h
 * @author AAbhiroop Datta (abhiroopdatta7@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-10-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __PCAPNG_NETBUFFER_H__
#define __PCAPNG_NETBUFFER_H__

#include <arpa/inet.h>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <list>
#include <ostream>
#include <sys/types.h>
#include <vector>

namespace PCapNG
{

class Buffer
{
    /**
     * @brief
     *
     */
  public:
    inline Buffer &operator<<(uint8_t &val)
    {
        uint8_t tmp = val;
        uint8_t *ptr = (uint8_t *)&tmp;
        _netBuffer.insert(_netBuffer.end(), ptr, ptr + sizeof(tmp));
        return *this;
    };

    inline Buffer &operator<<(uint16_t &val)
    {
        uint16_t tmp = htons(val);
        char *ptr = (char *)&tmp;
        _netBuffer.insert(_netBuffer.end(), ptr, ptr + sizeof(tmp));
        return *this;
    };

    inline Buffer &operator<<(uint32_t &val)
    {
        uint32_t tmp = htonl(val);
        char *ptr = (char *)&tmp;
        _netBuffer.insert(_netBuffer.end(), ptr, ptr + sizeof(tmp));
        return *this;
    };

    inline Buffer &operator<<(uint64_t &val)
    {
        uint64_t tmp = htobe64(val);
        char *ptr = (char *)&tmp;
        _netBuffer.insert(_netBuffer.end(), ptr, ptr + sizeof(tmp));
        return *this;
    };

    inline Buffer &operator<<(int64_t &val)
    {
        int64_t tmp = htobe64(val);
        char *ptr = (char *)&tmp;
        _netBuffer.insert(_netBuffer.end(), ptr, ptr + sizeof(tmp));
        return *this;
    };

    inline Buffer &operator<<(Buffer &val)
    {
        _netBuffer.insert(_netBuffer.end(), val._netBuffer.begin(), val._netBuffer.end());
        return *this;
    };

    inline void append(const char *buffer, size_t size)
    {
        _netBuffer.insert(_netBuffer.end(), buffer, (buffer + size));
    };

    char *data()
    {
        return _netBuffer.data();
    }

    size_t size()
    {
        return _netBuffer.size();
    }

  private:
    std::vector<char> _netBuffer;
};
} // namespace PCapNG

#endif /* __PCAPNG_BLOCKS_H__ */