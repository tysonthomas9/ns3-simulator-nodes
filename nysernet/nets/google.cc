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
    Ptr<CsmaChannel> net_google = CreateObject<CsmaChannel> ();
    // begin tap for net google.
    Ptr<Node> tap_google = CreateObject<Node> ();
    internet.Install(tap_google);
    Ptr<Ipv4> ipv4_tap_google = tap_google->GetObject<Ipv4> ();
    // begin netdevice config for tap_google, device tap_google.
    Ptr<CsmaNetDevice> dev_tap_google_tap_google = CreateObject<CsmaNetDevice> ();
    dev_tap_google_tap_google->SetAddress (Mac48Address ("54:52:00:c1:98:ea"));
    tap_google->AddDevice(dev_tap_google_tap_google);
    dev_tap_google_tap_google->SetQueue (CreateObject<DropTailQueue<Packet>> ());
    dev_tap_google_tap_google->Attach (net_google);
    int32_t devid_dev_tap_google_tap_google = ipv4_tap_google->AddInterface (dev_tap_google_tap_google);
    ipv4_tap_google->AddAddress(devid_dev_tap_google_tap_google, Ipv4InterfaceAddress (Ipv4Address ("10.0.0.1"), Ipv4Mask ("/24")));
    ipv4_tap_google->SetMetric (devid_dev_tap_google_tap_google, 1);
    ipv4_tap_google->SetUp (devid_dev_tap_google_tap_google);
    // end netdevice config for tap_google, device tap_google.
    tapBridge.SetAttribute ("DeviceName", StringValue ("tap0"));
    tapBridge.SetAttribute ("Mode", StringValue ("ConfigureLocal"));
    tapBridge.Install (tap_google, dev_tap_google_tap_google);
    // end tap for net google.
    Ptr<CsmaChannel> net_nysernet = CreateObject<CsmaChannel> ();
    // begin dist_bridge for net nysernet.
    Ptr<Node> dist_nysernet = CreateObject<Node> ();
    internet.Install(dist_nysernet);
    Ptr<Ipv4> ipv4_dist_nysernet = dist_nysernet->GetObject<Ipv4> ();
    // begin netdevice config for dist_nysernet, device dist_nysernet.
    Ptr<CsmaNetDevice> dev_dist_nysernet_dist_nysernet = CreateObject<CsmaNetDevice> ();
    dev_dist_nysernet_dist_nysernet->SetAddress (Mac48Address ("54:52:00:8a:e8:4c"));
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
    // begin router google_edge setup.
    Ptr<Node> router_google_edge = CreateObject<Node> ();
    internet.Install(router_google_edge);
    Ptr<Ipv4> ipv4_router_google_edge = router_google_edge->GetObject<Ipv4> ();
    // begin router google_edge device setup.
    // begin netdevice config for router_google_edge, device dev_google.
    Ptr<CsmaNetDevice> dev_router_google_edge_dev_google = CreateObject<CsmaNetDevice> ();
    dev_router_google_edge_dev_google->SetAddress (Mac48Address ("54:52:00:6a:d4:3e"));
    router_google_edge->AddDevice(dev_router_google_edge_dev_google);
    dev_router_google_edge_dev_google->SetQueue (CreateObject<DropTailQueue<Packet>> ());
    dev_router_google_edge_dev_google->Attach (net_google);
    int32_t devid_dev_router_google_edge_dev_google = ipv4_router_google_edge->AddInterface (dev_router_google_edge_dev_google);
    ipv4_router_google_edge->AddAddress(devid_dev_router_google_edge_dev_google, Ipv4InterfaceAddress (Ipv4Address ("10.0.0.2"), Ipv4Mask ("/24")));
    ipv4_router_google_edge->SetMetric (devid_dev_router_google_edge_dev_google, 1);
    ipv4_router_google_edge->SetUp (devid_dev_router_google_edge_dev_google);
    // end netdevice config for router_google_edge, device dev_google.
    // begin netdevice config for router_google_edge, device dev_nysernet.
    Ptr<CsmaNetDevice> dev_router_google_edge_dev_nysernet = CreateObject<CsmaNetDevice> ();
    dev_router_google_edge_dev_nysernet->SetAddress (Mac48Address ("54:52:00:a7:3f:c0"));
    router_google_edge->AddDevice(dev_router_google_edge_dev_nysernet);
    dev_router_google_edge_dev_nysernet->SetQueue (CreateObject<DropTailQueue<Packet>> ());
    dev_router_google_edge_dev_nysernet->Attach (net_nysernet);
    int32_t devid_dev_router_google_edge_dev_nysernet = ipv4_router_google_edge->AddInterface (dev_router_google_edge_dev_nysernet);
    ipv4_router_google_edge->AddAddress(devid_dev_router_google_edge_dev_nysernet, Ipv4InterfaceAddress (Ipv4Address ("199.109.9.3"), Ipv4Mask ("/24")));
    ipv4_router_google_edge->SetMetric (devid_dev_router_google_edge_dev_nysernet, 1);
    ipv4_router_google_edge->SetUp (devid_dev_router_google_edge_dev_nysernet);
    // end netdevice config for router_google_edge, device dev_nysernet.
    // end router google_edge device setup.
    // begin router google_edge bgp setup.
    Ptr<Bgp> bgp_router_google_edge = CreateObject<Bgp>();
    bgp_router_google_edge->SetAttribute("RouterID", Ipv4AddressValue("172.217.0.2"));
    bgp_router_google_edge->SetAttribute("LibbgpLogLevel", EnumValue(libbgp::INFO));
    // begin router google_edge bgp peer setup.
    Peer bgp_router_google_edge_peer_0;
    bgp_router_google_edge_peer_0.peer_address = "199.109.9.1";
    bgp_router_google_edge_peer_0.peer_asn = 3754;
    bgp_router_google_edge_peer_0.local_asn = 15169;
    bgp_router_google_edge_peer_0.passive = false;
    bgp_router_google_edge->AddPeer(bgp_router_google_edge_peer_0);
    // end router google_edge bgp peer setup.
    // begin router google_edge bgp nlri setup.
    bgp_router_google_edge->AddRoute("172.217.0.0", Ipv4Mask("/16"), "10.0.0.1");
    // end router google_edge bgp nlri setup.
    router_google_edge->AddApplication(bgp_router_google_edge);
    // end router google_edge bgp setup.
    // end router google_edge setup.
    // end routers.
    Simulator::Run();
    return 0;
    // end instance 0.
}
