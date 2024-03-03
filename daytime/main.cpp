#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;
int main() {
	struct sockaddr_in {
		short sin_family;
		unsigned short sin_port;
		struct in_addr sin_addr;
		char sin_zero[8];
	};
	struct in_addr {
		unsigned long s_addr;
	};
	int s = socket(AF_INET, SOCK_DGRAM, 0); // UDP
	if(s == -1) {
		cout << "Socket error\n";
		return 1;
	}
	sockaddr_in * self_addr = new (sockaddr_in);
	self_addr->sin_family = AF_INET; // интернет протокол IPv4
	self_addr->sin_port =0;
	self_addr->sin_addr.s_addr = 0;
	sockaddr_in * srv_addr = new (sockaddr_in);
	srv_addr->sin_family = AF_INET; // интернет протокол IPv4
	srv_addr->sin_port = htons(13);
	srv_addr->sin_addr.s_addr = inet_addr("132.163.96.3");
	int rc = connect(s,(const sockaddr*)srv_addr, sizeof(sockaddr_in));
	if (rc == -1) {
		cout << "Error: failed connect to server.\n";
		return 1;
	}
	else {
		cout << "We are connect to server!\n";
		char connection_msg[] = "Hello, it's client!";
		send(s, connection_msg, sizeof(connection_msg), 0);
		cout << "Сообщение отправлено" << endl;
		char daytime[512];
		recv(s, daytime, sizeof(daytime), 0);
		cout << "Сообщение принято" << endl;
		cout << "Daytime from server: " << daytime << endl;
		cout << "Session close!" << endl;
		close(s);
		delete srv_addr;
		return 0;
	}
}