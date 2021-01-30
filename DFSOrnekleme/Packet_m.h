//
// Generated file, do not edit! Created by nedtool 5.6 from Packet.msg.
//

#ifndef __PACKET_M_H
#define __PACKET_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0506
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Class generated from <tt>Packet.msg:2</tt> by nedtool.
 * <pre>
 * message Pack
 * {
 *     char PACKETTYPE;
 *     int CHILDRANK;
 * }
 * </pre>
 */
class Pack : public ::omnetpp::cMessage
{
  protected:
    char PACKETTYPE;
    int CHILDRANK;

  private:
    void copy(const Pack& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Pack&);

  public:
    Pack(const char *name=nullptr, short kind=0);
    Pack(const Pack& other);
    virtual ~Pack();
    Pack& operator=(const Pack& other);
    virtual Pack *dup() const override {return new Pack(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual char getPACKETTYPE() const;
    virtual void setPACKETTYPE(char PACKETTYPE);
    virtual int getCHILDRANK() const;
    virtual void setCHILDRANK(int CHILDRANK);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Pack& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Pack& obj) {obj.parsimUnpack(b);}


#endif // ifndef __PACKET_M_H

