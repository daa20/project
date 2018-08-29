#include <netdb.h>
#include <stdio.h>
#include <netinet/in.h>

#define DUMP(...)   printf(__VA_ARGS__)

int 
main(int argc, char** argv)
{
    char    buf[1024];
    struct  hostent hostinfo,*phost;
    int     ret;

    DUMP("argc:%d\n", argc);
    if(argc < 2 ) {
        printf("ERROR:test domainname\n");
        return 1;
    }

    if(gethostbyname_r(argv[1], &hostinfo, buf, sizeof(buf), &phost, &ret))
    
        printf("ERROR:gethostbyname(%s) ret: %d, phost: %d\n", argv[1], ret, (int)phost);
   
    else{
        int i;
        
        printf("gethostbyname(%s) success:ret:%d,", argv[1], ret);
        
        if(phost)
            printf("phost(%d): name: %s, addrtype: %d(AF_INET: %d), len: %d, addr[0]: %d,[1]:%d\n", 
                    (int)phost,phost->h_name,phost->h_addrtype,AF_INET,
                    phost->h_length,
                    (int)phost->h_addr_list[0],
                    phost->h_addr_list[0] == NULL ? 0 : (int)phost->h_addr_list[1]);

        for(i = 0; hostinfo.h_aliases[i]; i++)
            printf("host(%d) alias is: %s\n", (int)&hostinfo, hostinfo.h_aliases[i]);
        
        for(i = 0; hostinfo.h_addr_list[i]; i++)
            printf("host addr is:%s\n",inet_ntoa(*(struct in_addr*)hostinfo.h_addr_list[i]));
    }

    return 0;
}

