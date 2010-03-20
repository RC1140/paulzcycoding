#include <iostream>
#include <cstring>
using namespace std;

int main(int argc, char* argv[]) {
	const int MAXBUFFERSIZE = 201;
	char buf[MAXBUFFERSIZE];
	char *c;

	const char ENDOFINPUT[] = "ENDOFINPUT";

	cin.getline(buf, MAXBUFFERSIZE);
	while (strcmp(buf, ENDOFINPUT)) {
		cin.getline(buf, MAXBUFFERSIZE);
		for (c = buf; *c; ++c) {
			if (*c >= 'A' && *c <= 'Z') {
				*c = (*c - 'A' + 21) % 26 + 'A';
			}
		}
		cout << buf << endl;

		cin.getline(buf, MAXBUFFERSIZE);	//END
		cin.getline(buf, MAXBUFFERSIZE);	//NEXT HEADER
	}
	return 0;
}
