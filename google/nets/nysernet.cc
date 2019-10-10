#include <sys/socket.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/bgp.h"
#include "ns3/ipv4-address.h"
#include "ns3/drop-tail-queue.h"
#include "ns3/csma-module.h"
#include "ns3/distributed-bridge-helper.h"
using namespace ns3;
int main (void) {
    GlobalValue::Bind ("SimulatorImplementationType", StringValue ("ns3::RealtimeSimulatorImpl"));
    GlobalValue::Bind ("ChecksumEnabled", BooleanValue (true));
    InternetStackHelper internet;
    // begin instance 0 setup.
    // begin nets setup.
    Ptr<CsmaChannel> net_nysernet = CreateObject<CsmaChannel> ();
    // begin dist_bridge for net nysernet.
    Ptr<Node> dist_nysernet = CreateObject<Node> ();
    internet.Install(dist_nysernet);
    Ptr<Ipv4> ipv4_dist_nysernet = dist_nysernet->GetObject<Ipv4> ();
    // begin netdevice config for dist_nysernet, device dist_nysernet.
    Ptr<CsmaNetDevice> dev_dist_nysernet_dist_nysernet = CreateObject<CsmaNetDevice> ();
    dev_dist_nysernet_dist_nysernet->SetAddress (Mac48Address ("54:52:00:2f:1f:5e"));
    dist_nysernet->AddDevice(dev_dist_nysernet_dist_nysernet);
    dev_dist_nysernet_dist_nysernet->SetQueue (CreateObject<DropTailQueue<Packet>> ());
    dev_dist_nysernet_dist_nysernet->Attach (net_nysernet);
    int32_t devid_dev_dist_nysernet_dist_nysernet = ipv4_dist_nysernet->AddInterface (dev_dist_nysernet_dist_nysernet);
    ipv4_dist_nysernet->SetMetric (devid_dev_dist_nysernet_dist_nysernet, 1);
    ipv4_dist_nysernet->SetUp (devid_dev_dist_nysernet_dist_nysernet);
    // end netdevice config for dist_nysernet, device dist_nysernet.
    DistributedBridgeHelper disthelp_nysernet ("128.230.210.151", 9090, 1);
    disthelp_nysernet.Install(dist_nysernet, dev_dist_nysernet_dist_nysernet);
    // end dist_bridge for net nysernet.
    // end nets.
    // begin routers.
    // begin router nysernet_rs setup.
    Ptr<Node> router_nysernet_rs = CreateObject<Node> ();
    internet.Install(router_nysernet_rs);
    Ptr<Ipv4> ipv4_router_nysernet_rs = router_nysernet_rs->GetObject<Ipv4> ();
    // begin router nysernet_rs device setup.
    // begin netdevice config for router_nysernet_rs, device eth_nysernet.
    Ptr<CsmaNetDevice> dev_router_nysernet_rs_eth_nysernet = CreateObject<CsmaNetDevice> ();
    dev_router_nysernet_rs_eth_nysernet->SetAddress (Mac48Address ("54:52:00:87:23:e9"));
    router_nysernet_rs->AddDevice(dev_router_nysernet_rs_eth_nysernet);
    dev_router_nysernet_rs_eth_nysernet->SetQueue (CreateObject<DropTailQueue<Packet>> ());
    dev_router_nysernet_rs_eth_nysernet->Attach (net_nysernet);
    int32_t devid_dev_router_nysernet_rs_eth_nysernet = ipv4_router_nysernet_rs->AddInterface (dev_router_nysernet_rs_eth_nysernet);
    ipv4_router_nysernet_rs->AddAddress(devid_dev_router_nysernet_rs_eth_nysernet, Ipv4InterfaceAddress (Ipv4Address ("199.109.9.1"), Ipv4Mask ("/24")));
    ipv4_router_nysernet_rs->SetMetric (devid_dev_router_nysernet_rs_eth_nysernet, 1);
    ipv4_router_nysernet_rs->SetUp (devid_dev_router_nysernet_rs_eth_nysernet);
    // end netdevice config for router_nysernet_rs, device eth_nysernet.
    // end router nysernet_rs device setup.
    // begin router nysernet_rs bgp setup.
    Ptr<Bgp> bgp_router_nysernet_rs = CreateObject<Bgp>();
    bgp_router_nysernet_rs->SetAttribute("RouterID", Ipv4AddressValue("199.109.9.1"));
    bgp_router_nysernet_rs->SetAttribute("LibbgpLogLevel", EnumValue(libbgp::INFO));
    // begin router nysernet_rs bgp peer setup.
    Peer bgp_router_nysernet_rs_peer_0;
    bgp_router_nysernet_rs_peer_0.peer_address = "199.109.9.2";
    bgp_router_nysernet_rs_peer_0.peer_asn = 11872;
    bgp_router_nysernet_rs_peer_0.local_asn = 3754;
    bgp_router_nysernet_rs_peer_0.passive = false;
    bgp_router_nysernet_rs->AddPeer(bgp_router_nysernet_rs_peer_0);
    Peer bgp_router_nysernet_rs_peer_1;
    bgp_router_nysernet_rs_peer_1.peer_address = "199.109.9.3";
    bgp_router_nysernet_rs_peer_1.peer_asn = 15169;
    bgp_router_nysernet_rs_peer_1.local_asn = 3754;
    bgp_router_nysernet_rs_peer_1.passive = false;
    bgp_router_nysernet_rs->AddPeer(bgp_router_nysernet_rs_peer_1);
    // end router nysernet_rs bgp peer setup.
    router_nysernet_rs->AddApplication(bgp_router_nysernet_rs);
    // end router nysernet_rs bgp setup.
    // end router nysernet_rs setup.
    // end routers.
    Simulator::Run();
    return 0;
    // end instance 0.
}
