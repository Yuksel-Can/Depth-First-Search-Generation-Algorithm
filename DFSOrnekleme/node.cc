#include <string.h>
#include <omnetpp.h>
#include "Packet_m.h"

#define ROOT_NAME "node6"
using namespace omnetpp;

class node : public cSimpleModule{

    std::string parentGate;
    int parent;
    int myGateCount;
    int sendedGate;
    int myRank;

    std::vector<int> visited;

    protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(node);

void node::initialize(){
    parentGate="";
    parent=-1;
    sendedGate=0;
    myGateCount=(this->gateCount()/2);

    for(int i=0;i<myGateCount;i++){
        this->visited.push_back(0);
    }
    if(strcmp(getName(),ROOT_NAME) == 0){
        parentGate=this->getName();
        parent=1;
        Pack *pk = new Pack("first",2);
        pk->setPACKETTYPE('t');     //token

        scheduleAt(0.0, pk);
    }

}

void node::handleMessage(cMessage *msg){

    cGate *incomedGate = msg-> getArrivalGate();

    Pack *pk=check_and_cast<Pack *>(msg);

    if(pk->getPACKETTYPE()=='t'){

        if(incomedGate == NULL){

            EV <<this->getName()<<" nın visited listesi :";
            for(int i=0; i<visited.size();i++){
                EV << visited.at(i)<< ", ";
            }
            EV<<"\n";

            if(myGateCount !=0){
                //sendedGate=0;
                if(sendedGate+1 <= myGateCount){

                    if(pk->arrivedOn("gate$i",sendedGate)){

                        this->sendedGate +=1;
                        this->visited[sendedGate]=1;
                    }

                    Pack *pkt = new Pack("token",2);
                    pkt->setPACKETTYPE('t');
                    pkt->setCHILDRANK(sendedGate);

                    send(pkt,"gate$o",sendedGate);

                    this->visited[sendedGate]=1;
                    this->sendedGate +=1;

                    EV <<this->getName()<<" nın yeni visited listesi :";
                    for(int i=0; i<visited.size();i++){
                        EV << visited.at(i)<< ", ";
                    }
                    EV<<"\n";

                }
            }
        }else{

            EV <<this->getName()<<" ın visited listesi :";
            for(int i=0; i<visited.size();i++){
                EV << visited.at(i)<< ", ";
            }
            EV<<"\n";

            //EV <<this->getName()<<" nodunun göndereceği kapı"<<this->sendedGate<<": \n";   acılabilir
            if(parent==-1){


                parent=incomedGate->getIndex();
                parentGate=incomedGate->getName();
                //EV<<" parent : "<<parent<<", parentGate : "<<parentGate<<" .  \n";
                myRank = pk->getCHILDRANK();


                if(pk->arrivedOn("gate$i",sendedGate)){

                    this->visited[sendedGate]=1;
                    this->sendedGate +=1;
                }

                Pack *pkt = new Pack("token",2);
                pkt->setPACKETTYPE('t');
                pkt->setCHILDRANK(this->sendedGate);

                //EV <<this->getName()<<" nodunun gönderdiği kapı "<<this->sendedGate<<": \n";          acılabilir
                send(pkt,"gate$o",this->sendedGate);

                this->visited[this->sendedGate]=1;
                this->sendedGate +=1;


                EV <<this->getName()<<" nın yeni visited listesi :";
                for(int i=0; i<visited.size();i++){
                    EV << visited.at(i)<< ", ";
                }
                EV<<"\n";

            }else{

                if(strcmp(pk->getName(),"token") == 0){

                    Pack *pkt = new Pack("return",2);
                    pkt->setPACKETTYPE('t');
                    pkt->setCHILDRANK(pk->getCHILDRANK());

                    //EV <<this->getName()<<" nodunun gönderdiği kapı "<<incomedGate->getIndex()<<": \n";       acılabilir

                    this->visited[this->sendedGate]=1;
                    sendedGate += 1;

                    send(pkt,"gate$o",incomedGate->getIndex());

                    EV <<this->getName()<<" nın yeni visited listesi :";
                    for(int i=0; i<visited.size();i++){
                        EV << visited.at(i)<< ", ";
                    }
                    EV<<"\n";

                }else if(strcmp(pk->getName(),"return") == 0){

                    if(this->sendedGate < myGateCount-1){

                        if(pk->arrivedOn("gate$i",sendedGate)){

                            this->sendedGate +=1;
                            this->visited[sendedGate]=1;

                        }

                        Pack *pkt = new Pack("token",2);
                        pkt->setPACKETTYPE('t');
                        pkt->setCHILDRANK(this->sendedGate);

                       // EV <<this->getName()<<" nodunun gönderdiği kapı "<<this->sendedGate<<": \n";          acılabilir

                        send(pkt,"gate$o",this->sendedGate);

                        this->visited[this->sendedGate]=1;
                        this->sendedGate +=1;

                        EV <<this->getName()<<" nın yeni visited listesi :";
                        for(int i=0; i<visited.size();i++){
                            EV << visited.at(i)<< ", ";
                        }
                        EV<<"\n";

                    }else{
                        if(parentGate==this->getName()){

                            //bitti
                        }else{

                            Pack *pkt = new Pack("return",2);
                            pkt->setPACKETTYPE('t');
                            pkt->setCHILDRANK(this->myRank);

                          //  EV <<this->getName()<<" nodunun gönderdiği kapı " <<parent<<": \n";               acılabilir

                            send(pkt,"gate$o",parent);

                        }
                    }
                }



            }

        }
    }
}


