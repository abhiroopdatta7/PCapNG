
#include "PCapNG.h"
#include <cstddef>

int main()
{
    auto pcapNgFile = ::PCapNG::File("./build/test.pcapng");

    auto secHdr = ::PCapNG::SectionHeader();
    secHdr.AddHWDesc("My-PC");
    secHdr.AddOSDesc("Ubuntu");

    pcapNgFile.writeToFile(secHdr);

    auto interface = ::PCapNG::InterfaceDescription(::PCapNG::InterfaceDescription::LINKTYPE_ETHERNET);
    interface.AddInterfaceName("eth1");
    pcapNgFile << interface;

    auto packet = ::PCapNG::EnhancedPacket(0, 11, 12, 0, 0, NULL);
    pcapNgFile << packet;

    pcapNgFile.Close();
    return 0;
}