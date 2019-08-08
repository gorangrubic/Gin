/*==============================================================================

 Copyright 2018 by Roland Rabien
 For more information visit www.rabiensoftware.com

 ==============================================================================*/

#pragma once

class SecureStreamingSocket
{
public:
    SecureStreamingSocket (bool secure);

    bool connect (const String& remoteHostname, int remotePortNumber, int timeOutMillisecs = 3000);
    
    int read (void* destBuffer, int maxBytesToRead, bool blockUntilSpecifiedAmountHasArrived);
    int write (const void* sourceBuffer, int numBytesToWrite);

private:
    class Impl;
    std::unique_ptr<Impl> impl;
    std::unique_ptr<StreamingSocket> normalSocket;
    
};
