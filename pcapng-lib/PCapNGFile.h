/**
 * @file PCapNGFile.h
 * @author Abhiroop Datta (abhiroopdatta7@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-10-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __PCAPNG_FILE_H__
#define __PCAPNG_FILE_H__

#include "PCapNGBase.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sys/types.h>

namespace PCapNG
{
class File
{
    /**
     * @brief
     *
     */
  public:
    File()
    {
    }
    File(::std::string path)
    {
        try
        {
            _file.open(path, ::std::ios::out | ::std::ios::trunc | ::std::ios::binary);
        }
        catch (::std::filesystem::filesystem_error const &ex)
        {
            ::std::cout << "what():  " << ex.what() << '\n'
                        << "path1(): " << ex.path1() << '\n'
                        << "path2(): " << ex.path2() << '\n'
                        << "code().value():    " << ex.code().value() << '\n'
                        << "code().message():  " << ex.code().message() << '\n'
                        << "code().category(): " << ex.code().category().name() << '\n';
        }
    }

    bool IsOpen()
    {
        return _file.is_open();
    }

    void Close()
    {
        if (_file.is_open())
            _file.close();
    }

    File &operator<<(Block &block)
    {
        if ((*this)._file.is_open())
            (*this)._file << block;
        return *this;
    }

    void writeToFile(Block &block)
    {
        if (_file.is_open())
            _file << block;
    }

  private:
    ::std::ofstream _file;
};
} // namespace PCapNG

#endif /*  __PCAPNG_FILE_H__ */