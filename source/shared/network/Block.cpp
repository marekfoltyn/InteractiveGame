//
//  Block.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 23.01.16.
//
//

#include "Block.h"

Block::Block(const char * d, unsigned int len ){
    
    length = len+1;
    data = new char[length];
    memccpy(data, d, length, sizeof(char));
    
    // default values
    priority = PacketPriority::LOW_PRIORITY;
    reliability = PacketReliability::UNRELIABLE;
    address = RakNet::UNASSIGNED_SYSTEM_ADDRESS;
}

Block * Block::create(const char * data, unsigned int len ){
    
    return new Block(data, len);
}


void Block::setType(unsigned char type){
    
    data[0] = type;
}


unsigned char Block::getType(){
    
    return data[0];
}


void Block::setReliability( PacketReliability r ){

    reliability = r;
}


PacketReliability Block::getReliability(){
    
    return reliability;
}


void Block::setPriority( PacketPriority p ){

    priority = p;
}


PacketPriority Block::getPriority(){
    
    return priority;
}


void Block::setAddress( RakNet::SystemAddress addr ){
    
    address = addr;
}


RakNet::SystemAddress Block::getAddress(){
    
    return address;
}


const char * Block::getData(){
    
    return data+1; // skip the packet type
}

const int Block::getLength(){
    
    return length-1; // skip the packet type
}

const char * Block::getPacketData(){
    
    return data;
}


const int Block::getPacketLength(){
    
    return length;
}


void Block::dealloc(){

    delete [] data;
}

