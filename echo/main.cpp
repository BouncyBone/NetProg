#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[])
{
    struct sockaddr_in {
        short sin_family;
        unsigned short sin_port;
        struct in_addr sin_addr;
        char sin_zero[8];
    };
    struct in_addr {
        unsigned long s_addr;
    };

    int s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == -1) {
        exit(1);
    }
	
    sockaddr_in * srv_addr = new (sockaddr_in);
    srv_addr->sin_family = AF_INET;
    srv_addr->sin_port = htons(13);
    srv_addr->sin_addr.s_addr = inet_addr("132.163.96.3");

    int rc = connect(s,(const sockaddr*)srv_addr, sizeof(sockaddr_in));
    if (rc == -1) {
        cout << "Ошибка\n";
        return 1;
    } else {
        char msg[] = "HELLO_WORLD";
        send(s, msg, sizeof(msg), 0);
        cout << "Было отправлено: " << msg << endl;
        char returned_msg[512];
        recv(s, returned_msg, sizeof(returned_msg), 0);
        cout << "Было получено: " << returned_msg << endl;
    }
    close(s);
	delete(srv_addr);
    return 0;
}