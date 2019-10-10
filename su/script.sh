#!/bin/bash

echo net.ipv4.ip_forward=1 > /etc/sysctl.conf && sysctl -p

ifconfig

tunctl -t tap1
ip li set tap1 up

brctl addbr br0
brctl addif br0 tap1

tunctl -t tap0
ip li set tap0 up
brctl addif br0 tap0

ip addr add 128.230.0.1/32 dev br0

ip rou add 128.230.210.151/32 via 172.18.0.1 dev eth0

ip li set br0 up

route -n

traceroute google.com

ifconfig
openvpn --config /etc/openvpn/openvpn.conf &
waf --run su
# uml-utilities
