#!/bin/bash

iptables -t nat -A POSTROUTING -j MASQUERADE

{
    sleep 10
    tunctl -t tap0
    ip route add 128.230.0.0/16 via 10.0.0.2 dev tap0
    ip route add 128.230.210.151/32 via 172.18.0.1 dev eth0
} &

