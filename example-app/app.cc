
#include "PCapNG.h"
#include <cstddef>

using namespace PCapNG;
int main()
{
    auto pcapNgFile = File("./build/test.pcapng");

    auto secHdr = SHB();
    auto hwDesc = Option(OPTION_SHB_HW, "My-PC");
    auto osDesc = Option(OPTION_SHB_OS, "Ubuntu-20.04-LTS");
    secHdr.appendOption(&hwDesc);
    secHdr.appendOption(&osDesc);

    pcapNgFile.writeToFile(secHdr);

    auto interface = IDB(IDB_LINKTYPE_ETHERNET);
    auto if_name = Option(OPTION_IDB_IF_NAME, "eth1");
    interface.appendOption(&if_name);
    pcapNgFile << interface;

    auto packet = EPB(0, 11, 12, 0, 0, NULL);
    pcapNgFile << packet;

    pcapNgFile.Close();
    return 0;
}