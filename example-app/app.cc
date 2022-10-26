
#include "PCapNG.h"
#include <cstddef>

using namespace PCapNG;
int main()
{
    auto pcapNgFile = File("./build/test.pcapng");

    auto secHdr = SectionHeader();
    secHdr.AddHWDesc("My-PC");
    secHdr.AddOSDesc("Ubuntu");

    pcapNgFile.writeToFile(secHdr);

    auto interface = InterfaceDescription(InterfaceDescription::LINKTYPE_ETHERNET);
    interface.AddInterfaceName("eth1");
    pcapNgFile << interface;

    auto packet = EnhancedPacket(0, 11, 12, 0, 0, NULL);
    pcapNgFile << packet;

    pcapNgFile.Close();
    return 0;
}