#include "QNtp.h"

QNtp::QNtp()
{
    qDebug()<<"CREATING..";
}
void QNtp::setNtp(bool ntp){

    if(!ntp){
        return;
    }else{
        int sockfd, n;

        int portno = 123;

        char* host_name = "us.pool.ntp.org";



        typedef struct
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


        ntp_packet packet = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

        memset( &packet, 0, sizeof( ntp_packet ) );


        *( ( char * ) &packet + 0 ) = 0x1b;



        struct sockaddr_in serv_addr;
        struct hostent *server;

        sockfd = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );

        if ( sockfd < 0 )
            return;

        server = gethostbyname( host_name );

        if ( server == NULL )
            return



                    bzero( ( char* ) &serv_addr, sizeof( serv_addr ) );

        serv_addr.sin_family = AF_INET;



        bcopy( ( char* )server->h_addr, ( char* ) &serv_addr.sin_addr.s_addr, server->h_length );



        serv_addr.sin_port = htons( portno );



        if ( connect( sockfd, ( struct sockaddr * ) &serv_addr, sizeof( serv_addr) ) < 0 )
            return;



        n = write( sockfd, ( char* ) &packet, sizeof( ntp_packet ) );

        if ( n < 0 )
            return;



        n = read( sockfd, ( char* ) &packet, sizeof( ntp_packet ) );

        if ( n < 0 )
            return;



        packet.txTm_s = ntohl( packet.txTm_s ); // Time-stamp seconds.
        packet.txTm_f = ntohl( packet.txTm_f ); // Time-stamp fraction of a second.





        struct timespec tm;

        tm.tv_sec=packet.txTm_s-NTP_TIMESTAMP_DELTA;


        int result =clock_settime(CLOCK_REALTIME,&tm);
        Q_UNUSED(result);


    }
}


