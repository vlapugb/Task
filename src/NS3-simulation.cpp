#include <ns3/core-module.h>
#include <ns3/network-module.h>
#include <ns3/mobility-module.h>
#include <ns3/lte-module.h>
#include <ns3/internet-module.h>
using namespace ns3;

//define's for simpe code

#define pfff "ns3::PfFfMacScheduler"
#define const_pos_model "ns3::ConstantPositionMobilityModel"

int main()
{
  // creating UE and ENB (2 and 1)
  
  Ptr<LteHelper> lteHelper = CreateObject<LteHelper>();

  NodeContainer enbNodes;
  enbNodes.Create(1);
  NodeContainer ueNodes;
  ueNodes.Create(2);

  // creating class instance for using mobility 

  MobilityHelper mobility;

  // setup the position of ue's 

  Ptr<ListPositionAllocator> UEposition = CreateObject<ListPositionAllocator>();
  UEposition->Add(Vector(0.0, 0.0, 0.0));
  UEposition->Add(Vector(1.0, 1.0, 1.0));
  mobility.SetPositionAllocator(UEposition);
  mobility.SetMobilityModel(const_pos_model);
  mobility.Install(ueNodes);

  // setup the position of enb

  Ptr<ListPositionAllocator> ENBposition = CreateObject<ListPositionAllocator>();
  ENBposition->Add(Vector(0.0, 0.0, 0.0));
  mobility.SetPositionAllocator(ENBposition);
  mobility.SetMobilityModel(const_pos_model);
  mobility.Install(enbNodes);

  // setup PfFfMacScheduler

  lteHelper->SetSchedulerType(pfff);

  // install LTE settings on UE and ENB devices

  NetDeviceContainer enbDevs;
  enbDevs = lteHelper->InstallEnbDevice(enbNodes);
  NetDeviceContainer ueDevs;
  ueDevs = lteHelper->InstallUeDevice(ueNodes);
  lteHelper->Attach(ueDevs, enbDevs.Get(0));

  // setup saturation traffic (in UL and in DL)

  enum EpsBearer::Qci q = EpsBearer::GBR_CONV_VOICE;
  EpsBearer bearer(q);
  lteHelper->ActivateDataRadioBearer(ueDevs, bearer);

  // tracing RLC and MAC

  lteHelper->EnableMacTraces();
  lteHelper->EnableRlcTraces();

  // activating simulation

  Simulator::Stop(Seconds(0.5));
  Simulator::Run();
  Simulator::Destroy();

  return 0;
}