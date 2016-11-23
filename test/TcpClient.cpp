//
// Created by DengXu on 31/10/2016.
//

#include "TcpClient.h"

int main(int argc, char *argv[])
{
    TcpClient client;
    client.Connect("127.0.0.1", 8000);
    return 0;
}