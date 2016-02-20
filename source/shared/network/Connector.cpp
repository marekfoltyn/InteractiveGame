#include "Connector.h"

#include <cstring>
#include <string>
#include <stdlib.h>

using namespace GameNet;

Connector * Connector::instance = nullptr;


Connector * Connector::getInstance(){
    if(instance == nullptr) {
        instance = new Connector();
    }
    return instance;
}


bool Connector::start(){
    return startAsServer(1);
}


bool Connector::startAsServer(unsigned short maxPlayers)
{    
    server = RakNet::UNASSIGNED_SYSTEM_ADDRESS;
    
    // raknet interface configuration
    raknetInterface= RakNet::RakPeerInterface::GetInstance();
	raknetInterface->SetTimeoutTime(CONNECTION_LOST_TIMEOUT, RakNet::UNASSIGNED_SYSTEM_ADDRESS);
	raknetInterface->SetOccasionalPing(true);
	raknetInterface->SetIncomingPassword("abc", strlen("abc"));
    raknetInterface->SetMaximumIncomingConnections(maxPlayers);
    //interface->SetUnreliableTimeout(CONNECTION_LOST_TIMEOUT);
    
    // socket descriptor settings
    RakNet::SocketDescriptor socketDescriptors[1];
    socketDescriptors[0].port = (maxPlayers>1) ? SERVER_PORT : CLIENT_PORT;
    socketDescriptors[0].socketFamily=AF_INET; // IPV4
    
    // try 10 ports
    bool result = false;
    for(int i=0; i<10; i++)
    {
        result = raknetInterface->Startup(maxPlayers, socketDescriptors, 1) == RakNet::RAKNET_STARTED; // last arg is socketDescriptor count
        if(result == true) {
            LOG("Servers started on port %d.\n", socketDescriptors[0].port);
            break;
        } else {
            LOG("Server failed to start on port %d. Trying next...\n", socketDescriptors[0].port);
            socketDescriptors[0].port++;
            continue;
        }
    }
    
    if (result == false){
        LOG("Server failed to start on EACH PORT!!.\n");
        RakNet::RakPeerInterface::DestroyInstance(raknetInterface);
        raknetInterface = nullptr;
        return false;
    }
    
    // logging used socket addresses
    
    DataStructures::List< RakNet::RakNetSocket2* > sockets;
	raknetInterface->GetSockets(sockets);
    
    /*LOG("Socket addresses used by Connector:\n==========================\n");
    for (unsigned int i=0; i < sockets.Size(); i++)
    {
        LOG("%i. %s\n", i+1, sockets[i]->GetBoundAddress().ToString(true));
    }*/
    
    LOG("\nMy IP addresses:\n");
	for (unsigned int i = 0; i < raknetInterface->GetNumberOfAddresses(); i++)
    {
		RakNet::SystemAddress sa = raknetInterface->GetInternalID(RakNet::UNASSIGNED_SYSTEM_ADDRESS, i);
        LOG("%i. %s:%i\n", i+1, sa.ToString(false), sa.GetPort());
    }
    
    // server name
    if(maxPlayers>1){
		raknetInterface->SetOfflinePingResponse("Unnamed Server", strlen("Unnamed Server") + 1); // '\0' is automatically added in "hello"
    }
    
    return true;
}


void Connector::stop(){
    
	if (raknetInterface == nullptr) {
        return;
    }
    
	raknetInterface->Shutdown(0); // 0 ... dont wait for stopping connections
	RakNet::RakPeerInterface::DestroyInstance(raknetInterface);
	raknetInterface = nullptr;
}


void Connector::connect( RakNet::SystemAddress server ){
   
	if (raknetInterface == nullptr){
        LOG("Client is not started!");
        return;
    }
    
    char * ip = new char[64]; // must be new char[]! Not char ip[], BAD_ACCESS!!
    for(int i=0; i<64; i++){ ip[i] = 0; }
        
    server.ToString(false, ip);

	int result = raknetInterface->Connect(ip, server.GetPort(), "abc", (int)strlen("abc"));
    LOG("[Connector] Connecting to %s", ip);
    if(result == RakNet::CONNECTION_ATTEMPT_STARTED)
    {
        LOG("[Connector] Connecting to %s started.", ip);
    }
    else if (result == RakNet::INVALID_PARAMETER)
    {
        LOG("[Connector] INVALID_PARAMETER");
    }
    else if (result == RakNet::CANNOT_RESOLVE_DOMAIN_NAME)
    {
        LOG("[Connector] CANNOT_RESOLVE_DOMAIN_NAME");
    }

    else if (result == RakNet::ALREADY_CONNECTED_TO_ENDPOINT)
    {
        LOG("[Connector] ALREADY_CONNECTED_TO_ENDPOINT");
    }

    else if (result == RakNet::CONNECTION_ATTEMPT_ALREADY_IN_PROGRESS)
    {
        LOG("[Connector] CONNECTION_ATTEMPT_ALREADY_IN_PROGRESS");
    }

    else if (result == RakNet::SECURITY_INITIALIZATION_FAILED)
    {
        LOG("[Connector] SECURITY_INITIALIZATION_FAILED");
    }
    else{
        LOG("[Connector] connecting atempt failed for unknown reason!!!");
    }
    
    delete [] ip;
}


void Connector::disconnect( RakNet::SystemAddress address ){
    if (raknetInterface == nullptr) {
        return;
    }
	raknetInterface->CloseConnection(address, true); // true ... send disconnection notification
    server = RakNet::UNASSIGNED_SYSTEM_ADDRESS;
}


void Connector::send(Box* b){
	if (raknetInterface == nullptr){
        return;
    }
    
	raknetInterface->Send(b->getPacketData(), b->getPacketLength(), b->getPriority(), b->getReliability(), 0, b->getAddress(), false);
}


Box * Connector::receive(){
    
	if (raknetInterface == nullptr) {
        return 0;
    }
    
	RakNet::Packet * p = raknetInterface->Receive();

    if(p == nullptr)
    {
        return nullptr;
    }
    else
    {
        /*/debug
        LOG("Packet:\n=======\n");
        LOG("type: %d\n", p->data[0]);
        LOG("length: %d\n", p->length);
        LOG("data: ");
        for(int i=1; i < p->length; i++) {
            LOG("[%c]", p->data[i]);
        }
        LOG("\n");*/

        // set server to Connector
        if(p->data[0] == P_CONNECTED){
            server = p->systemAddress;
        }
        
        if(p->data[0] == P_CONNECTION_LOST){
            server = RakNet::UNASSIGNED_SYSTEM_ADDRESS;
        }
        
        return Box::create(p);
    }
}


void Connector::setServerName(std::string name){
	if (raknetInterface == nullptr){
        return;
    }
    
	raknetInterface->SetOfflinePingResponse(name.c_str(), (unsigned int)name.length() + 1);
}


std::string Connector::getServerName(){
	if (raknetInterface == nullptr){
        LOG("Server not started - returning default name");
        return "Phone Stadium";
    }
    
    char * name;
    unsigned int len;
	raknetInterface->GetOfflinePingResponse(&name, &len);
    return name;
}

void Connector::ping(){

	if (raknetInterface == nullptr){
        return;
    }
    
    for(int i=0; i<10; i++){
        raknetInterface->Ping("255.255.255.255", SERVER_PORT+i, true); // true ... reply only if server is not full
    }
}

RakNet::SystemAddress Connector::getServer(){
    return server;
}