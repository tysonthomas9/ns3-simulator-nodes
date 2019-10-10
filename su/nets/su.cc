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
#include "ns3/tap-bridge-module.h"
#include "ns3/distributed-bridge-helper.h"
using namespace ns3;
int main (void) {
    GlobalValue::Bind ("SimulatorImplementationType", StringValue ("ns3::RealtimeSimulatorImpl"));
    GlobalValue::Bind ("ChecksumEnabled", BooleanValue (true));
    InternetStackHelper internet;
    TapBridgeHelper tapBridge;
    // begin instance 0 setup.
    // begin nets setup.
    Ptr<CsmaChannel> net_su = CreateObject<CsmaChannel> ();
    // begin tap for net su.
    Ptr<Node> tap_su = CreateObject<Node> ();
    internet.Install(tap_su);
    Ptr<Ipv4> ipv4_tap_su = tap_su->GetObject<Ipv4> ();
    // begin netdevice config for tap_su, device tap_su.
    Ptr<CsmaNetDevice> dev_tap_su_tap_su = CreateObject<CsmaNetDevice> ();
    dev_tap_su_tap_su->SetAddress (Mac48Address ("54:52:00:f8:77:73"));
    tap_su->AddDevice(dev_tap_su_tap_su);
    dev_tap_su_tap_su->SetQueue (CreateObject<DropTailQueue<Packet>> ());
    dev_tap_su_tap_su->Attach (net_su);
    int32_t devid_dev_tap_su_tap_su = ipv4_tap_su->AddInterface (dev_tap_su_tap_su);
    ipv4_tap_su->AddAddress(devid_dev_tap_su_tap_su, Ipv4InterfaceAddress (Ipv4Address ("128.230.0.1"), Ipv4Mask ("/16")));
    ipv4_tap_su->SetMetric (devid_dev_tap_su_tap_su, 1);
    ipv4_tap_su->SetUp (devid_dev_tap_su_tap_su);
    // end netdevice config for tap_su, device tap_su.
    tapBridge.SetAttribute ("DeviceName", StringValue ("tap0"));
    tapBridge.SetAttribute ("Mode", StringValue ("UseBridge"));
    tapBridge.Install (tap_su, dev_tap_su_tap_su);
    // end tap for net su.
    Ptr<CsmaChannel> net_nysernet = CreateObject<CsmaChannel> ();
    // begin dist_bridge for net nysernet.
    Ptr<Node> dist_nysernet = CreateObject<Node> ();
    internet.Install(dist_nysernet);
    Ptr<Ipv4> ipv4_dist_nysernet = dist_nysernet->GetObject<Ipv4> ();
    // begin netdevice config for dist_nysernet, device dist_nysernet.
    Ptr<CsmaNetDevice> dev_dist_nysernet_dist_nysernet = CreateObject<CsmaNetDevice> ();
    dev_dist_nysernet_dist_nysernet->SetAddress (Mac48Address ("54:52:00:cc:eb:e8"));
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
    // begin router su_edge setup.
    Ptr<Node> router_su_edge = CreateObject<Node> ();
    internet.Install(router_su_edge);
    Ptr<Ipv4> ipv4_router_su_edge = router_su_edge->GetObject<Ipv4> ();
    // begin router su_edge device setup.
    // begin netdevice config for router_su_edge, device eth_su.
    Ptr<CsmaNetDevice> dev_router_su_edge_eth_su = CreateObject<CsmaNetDevice> ();
    dev_router_su_edge_eth_su->SetAddress (Mac48Address ("54:52:00:86:51:90"));
    router_su_edge->AddDevice(dev_router_su_edge_eth_su);
    dev_router_su_edge_eth_su->SetQueue (CreateObject<DropTailQueue<Packet>> ());
    dev_router_su_edge_eth_su->Attach (net_su);
    int32_t devid_dev_router_su_edge_eth_su = ipv4_router_su_edge->AddInterface (dev_router_su_edge_eth_su);
    ipv4_router_su_edge->AddAddress(devid_dev_router_su_edge_eth_su, Ipv4InterfaceAddress (Ipv4Address ("128.230.0.2"), Ipv4Mask ("/16")));
    ipv4_router_su_edge->SetMetric (devid_dev_router_su_edge_eth_su, 1);
    ipv4_router_su_edge->SetUp (devid_dev_router_su_edge_eth_su);
    // end netdevice config for router_su_edge, device eth_su.
    // begin netdevice config for router_su_edge, device eth_nysernet.
    Ptr<CsmaNetDevice> dev_router_su_edge_eth_nysernet = CreateObject<CsmaNetDevice> ();
    dev_router_su_edge_eth_nysernet->SetAddress (Mac48Address ("54:52:00:97:b3:00"));
    router_su_edge->AddDevice(dev_router_su_edge_eth_nysernet);
    dev_router_su_edge_eth_nysernet->SetQueue (CreateObject<DropTailQueue<Packet>> ());
    dev_router_su_edge_eth_nysernet->Attach (net_nysernet);
    int32_t devid_dev_router_su_edge_eth_nysernet = ipv4_router_su_edge->AddInterface (dev_router_su_edge_eth_nysernet);
    ipv4_router_su_edge->AddAddress(devid_dev_router_su_edge_eth_nysernet, Ipv4InterfaceAddress (Ipv4Address ("199.109.9.2"), Ipv4Mask ("/24")));
    ipv4_router_su_edge->SetMetric (devid_dev_router_su_edge_eth_nysernet, 1);
    ipv4_router_su_edge->SetUp (devid_dev_router_su_edge_eth_nysernet);
    // end netdevice config for router_su_edge, device eth_nysernet.
    // end router su_edge device setup.
    // begin router su_edge bgp setup.
    Ptr<Bgp> bgp_router_su_edge = CreateObject<Bgp>();
    bgp_router_su_edge->SetAttribute("RouterID", Ipv4AddressValue("128.230.0.2"));
    bgp_router_su_edge->SetAttribute("LibbgpLogLevel", EnumValue(libbgp::INFO));
    // begin router su_edge bgp peer setup.
    Peer bgp_router_su_edge_peer_0;
    bgp_router_su_edge_peer_0.peer_address = "199.109.9.1";
    bgp_router_su_edge_peer_0.peer_asn = 3754;
    bgp_router_su_edge_peer_0.local_asn = 11872;
    bgp_router_su_edge_peer_0.passive = false;
    bgp_router_su_edge->AddPeer(bgp_router_su_edge_peer_0);
    // end router su_edge bgp peer setup.
    // begin router su_edge bgp nlri setup.
    bgp_router_su_edge->AddRoute("128.230.0.0", Ipv4Mask("/16"), "128.230.0.1");
    // end router su_edge bgp nlri setup.
    router_su_edge->AddApplication(bgp_router_su_edge);
    // end router su_edge bgp setup.
    // end router su_edge setup.
    // end routers.
    Simulator::Run();
    return 0;
    // end instance 0.
}
