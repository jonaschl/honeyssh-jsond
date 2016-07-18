#!/bin/bash
mkdir -p /opt/honeyssh-transfer-daemon
echo -e "\033[32mCompile the daemon\033[0m"
make
make clean
cp daemon /opt/honeyssh-transfer-daemon/daemon
