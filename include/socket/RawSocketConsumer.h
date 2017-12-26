#pragma once

#include "ErrorSocket.h"
#include <tuple>

namespace RACconsumer
{
    class   RawSocketConsumer
    {
	public :

	RawSocketConsumer();

	int ConsumeQueueAndDecode();

	private :

	int DecodeRawData(std::tuple<const char*, int> *oData);
	RACerror::ErrorSocket            oRawSocketListenerError;
    };
}
