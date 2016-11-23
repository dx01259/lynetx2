#!/bin/bash

lldb ./TcpService -Wl,-rpath,/usr/local/lib,../../lib -lnet -ltinyxml2 -lbase -llog
