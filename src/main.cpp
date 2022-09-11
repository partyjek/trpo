// Project IPCALC

// Includes
#include "functions.cpp"
#include <iostream>
#include <string>

// Use "standart" namespace (string,cout,cin etc.)
using namespace std;

// Main function
int main()
{
    // Define variables
    string ip_net;
    int *ip_addr_mask;
    int *net_bcast;
    int **ip_bin;

    // Input IP address and Netmask
    cout << "Input IP/mask (ex. A-AAA.B-BBB.C-CCC.D-DDD/EE or "
            "A-AAA.B-BBB.C-CCC.D-DDD/xxx.xxx.xxx.xxx"
         << endl;
    cin >> ip_net;
    cout << endl;

    // Localize IP/mask with many types of input
    if ((ip_net.substr(ip_net.find('/') + 1, ip_net.length())).length() <= 2) {
        ip_addr_mask = gen_ip_array(ip_net);
    } else {
        ip_net = localize(ip_net);
        ip_addr_mask = gen_ip_array(ip_net);
    }

    // Print to user first part
    cout << "You input:  " << ip_net << endl << endl;
    print_p1(ip_addr_mask);

    // Generate binary IP and Netmask
    // (array[[A],[B],[C],[D],[M1],[M2],[M3],[M4]])
    ip_bin = dec2bin(ip_addr_mask);

    // Find Net adress and broadcast
    net_bcast = bin2addr(ip_bin);

    // Print to user second part
    print_p2(net_bcast);

    // Delete all arrays
    delete[] ip_addr_mask;
    delete[] net_bcast;
    for (int i = 0; i < 8; i++) {
        delete[] ip_bin[i];
    }
    delete[] ip_bin;

    return 0;
}
