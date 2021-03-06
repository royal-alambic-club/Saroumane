#include "LogHandler.h"
#include "RawSocket.h"
#include "JsonConfHandler.h"

#include <net/ethernet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <sys/ioctl.h>
#include <net/if.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h> /* the L2 protocols */

namespace RACsocket
{
    RawSocket::RawSocket()
    {
	Config();
	CreateSocket(); 
	if (bPromisc)
	{
	    PerformPromiscuousMode();
	}
	if (!oRawSocketError.IsError())
	{
	    LOG(INFO, "Raw Socket Tcp Creation : DONE SUCCESS");
	}
    }

    RawSocket::~RawSocket()
    {
	CloseSocket();
    }

    int RawSocket::CreateSocket()
    {
	fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (fd == -1)
	{
	    oRawSocketError.SetErrorStateAndLogErrorFromErno(true);
	}
	return fd;
    }

    int RawSocket::CloseSocket()
    {
	return close(fd);
    }

    void    RawSocket::PerformPromiscuousMode()
    {

	struct ifreq ifr;
	struct packet_mreq mr;

	ifr.ifr_ifindex = 0;
	strcpy(ifr.ifr_name, sInterface.c_str());

	if (ioctl(fd, SIOGIFINDEX, &ifr) < 0)
	{
	    perror("ioctl error ");
	    return ;
	}

	memset(&mr, 0, sizeof(mr));
	mr.mr_ifindex = ifr.ifr_ifindex;
	mr.mr_type =  PACKET_MR_PROMISC;

	if (setsockopt(fd, SOL_PACKET, PACKET_ADD_MEMBERSHIP,
		    (char *)&mr, sizeof(mr)) < 0)
	{
	    perror("setsockopt error ");
	    return ;
	}
    }

    int	RawSocket::Bind()
    {
	struct sockaddr_ll sll;
	struct ifreq ifr; bzero(&sll , sizeof(sll));
	bzero(&ifr , sizeof(ifr)); 
	strncpy((char *)ifr.ifr_name, sInterface.c_str(), IFNAMSIZ); 
	//copy device name to ifr 
	if((ioctl(fd , SIOCGIFINDEX , &ifr)) == -1)
	{ 
	    perror("Unable to find interface index");
	    exit(-1); 
	}
	sll.sll_family = AF_PACKET; 
	sll.sll_ifindex = ifr.ifr_ifindex; 
	sll.sll_protocol = htons(0x0800); 
	if((bind(fd, (struct sockaddr *)&sll , sizeof(sll))) ==-1)
	{
	    oRawSocketError.SetErrorStateAndLogErrorFromErno(true);
	    return -1;
	}
	return 1;
    }

    void    RawSocket::Config()
    {
	try{
	    iPort = RACconf::JsonConfHandler::GetValueFromConfigFile<int>("sniffer.port");
	    sIp = RACconf::JsonConfHandler::GetValueFromConfigFile<std::string>("sniffer.ip", "127.0.0.1");
	    sInterface = RACconf::JsonConfHandler::GetValueFromConfigFile<std::string>("sniffer.interface", "lo");
	    bPromisc = RACconf::JsonConfHandler::GetValueFromConfigFile<bool>("sniffer.promisc", false);
	}
	catch (std::exception &e)
	{
	    oRawSocketError.SetErrorStateAndLogOwnError(true, e.what());
	}
    }

    void        RawSocket::Error::SetErrorStateAndLogErrorFromErno(bool bErrorFlag)
    {
	SetErrorState(bErrorFlag);
	LogErrorFromErno();
    }

    void	RawSocket::Error::SetErrorStateAndLogOwnError(bool bErrorFlag, const char* pErrMsg)
    {
	SetErrorState(bErrorFlag);
	LogOwnError(pErrMsg);
    }
}
