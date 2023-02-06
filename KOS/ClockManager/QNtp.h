#ifndef QNTP_H
#define QNTP_H


#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <QDebug>
#define NTP_TIMESTAMP_DELTA 2208988800ull

#define LI(packet)   (uint8_t) ((packet.li_vn_mode & 0xC0) >> 6) // (li   & 11 000 000) >> 6
#define VN(packet)   (uint8_t) ((packet.li_vn_mode & 0x38) >> 3) // (vn   & 00 111 000) >> 3
#define MODE(packet) (uint8_t) ((packet.li_vn_mode & 0x07) >> 0) // (mode & 00 000 111) >> 0

class QNtp
{

    struct
    {

        uint8_t li_vn_mode;




        uint8_t stratum;
        uint8_t poll;
        uint8_t precision;

        uint32_t rootDelay;
        uint32_t rootDispersion;
        uint32_t refId;

        uint32_t refTm_s;
        uint32_t refTm_f;

        uint32_t origTm_s;
        uint32_t origTm_f;

        uint32_t rxTm_s;
        uint32_t rxTm_f;

        uint32_t txTm_s;
        uint32_t txTm_f;

    } ntp_packet;

public slots:
    void readDatagrams();
public:
    QNtp();
    void setNtp(bool ntp);


private:
    //int sockfd, n;
    //int portno = 123;
    // char* host_name = "us.pool.ntp.org";

};

#endif // QNTP_H
