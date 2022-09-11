// All of used functions is here

// Includes
#include <cmath>
#include <iostream>
#include <string>

// Use "standart" namespace (string,cout,cin etc.)
using namespace std;

// Function of localize netmask
inline string localize(string ip_net)
{
    // Define variables
    string delim_addr = ".", ip_addr_str;
    string delim_mask = "/", ip_mask_str, ip_mask_dig;
    int pos = ip_net.find(delim_mask);
    int ip_mask[4], mask = 0, j;

    // Split IP address and netmask
    ip_addr_str = ip_net.substr(0, pos + 1);
    ip_mask_dig = ip_net.substr(pos + 1, ip_net.length());

    // Get correct mask address
    try {
        for (int i = 0; i < 4; i++) {
            ip_mask[i]
                    = stoi(ip_mask_dig.substr(0, ip_mask_dig.find(delim_addr)));
            ip_mask_dig.erase(0, ip_mask_dig.find(delim_addr) + 1);
        }
    } catch (...) {
        cout << "Netmask contains illegal symbols" << endl;
        exit(0);
    }
    for (int i = 0; i < 4; i++) {
        j = 0;
        while (ip_mask[i] > 1) {
            mask++;
            ip_mask[i] -= pow(2, 7 - j);
            j++;
        }
        mask += ip_mask[i];
    }
    for (int i = 1; i < 4; i++) {
        if (ip_mask[i] > ip_mask[i - 1]) {
            cout << "Netmask is not correct" << endl;
            exit(0);
        }
    }
    ip_net = ip_addr_str + to_string(mask);

    return ip_net;
}

// Function of gen IP array
inline int *gen_ip_array(string ip_net)
{
    // Define variables
    int ip_addr_ar[4], ip_mask, ip_mask_dec, ip_mask_ar[4], i;
    string delim_addr = ".", ip_addr_str, ip_addr_dig;
    string delim_mask = "/", ip_mask_str, ip_mask_dig;
    int pos = ip_net.find(delim_mask);
    static int *ip_addr_mask = new int[8];

    // Split IP address and netmask
    ip_addr_dig = ip_net.substr(0, pos);
    ip_mask_dig = ip_net.substr(pos + 1, ip_net.length());

    // Create empty addr and mask
    for (i = 0; i < 4; i++) {
        ip_addr_ar[i] = 0;
        ip_mask_ar[i] = 0;
    }

    // Get correct IP address
    try {
        for (i = 0; i < 4; i++) {
            ip_addr_ar[i]
                    = stoi(ip_addr_dig.substr(0, ip_addr_dig.find(delim_addr)));
            ip_addr_dig.erase(0, ip_addr_dig.find(delim_addr) + 1);
        }
    } catch (...) {
        cout << "IP address contains illegal symbols" << endl;
        exit(0);
    }

    // Get correct mask
    try {
        ip_mask = stoi(ip_mask_dig);
    } catch (...) {
        cout << "Net mask is not integer" << endl;
        exit(0);
    }
    if (ip_mask < 0 || ip_mask > 32) {
        cout << "Net mask is not in range (0,32)" << endl;
        exit(0);
    }
    ip_mask_dec = 255 * (ip_mask / 8);
    for (i = 0; i < ip_mask - 8 * (ip_mask / 8); i++) {
        ip_mask_dec += pow(2, 7 - i);
    }
    i = 0;
    while (ip_mask_dec >= 256) {
        ip_mask_ar[i] = 255;
        i++;
        ip_mask_dec -= 255;
    }
    ip_mask_ar[i] = ip_mask_dec;

    // Building output
    for (i = 0; i < 4; i++) {
        ip_addr_mask[i] = ip_addr_ar[i];
        ip_addr_mask[i + 4] = ip_mask_ar[i];
    }

    return ip_addr_mask;
}

// Function of convert standart IP/NET to binary mode
inline int **dec2bin(int *ip)
{
    // Define variables
    static int **ip_bin = new int *[8];

    // Decode dec to bin[8]
    for (int i = 0; i < 8; i++)
        ip_bin[i] = new int[8];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (ip[i] >= pow(2, 7 - j)) {
                ip_bin[i][j] = 1;
                ip[i] -= pow(2, 7 - j);
            } else {
                ip_bin[i][j] = 0;
            }
        }
    }

    return ip_bin;
}

// Function or convert binary IP/NET to standart mode
inline int *bin2addr(int **ip_bin)
{
    // Define variables
    static int *net_bcast = new int[12];
    int wcard[4], wcard_bin[4][8];

    // Generate arrays with zero values
    for (int i = 0; i < 8; i++) {
        net_bcast[i] = 0;
        wcard[i] = 0;
    }

    // Generate wildcard
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            if (ip_bin[i + 4][j] == 0) {
                wcard_bin[i][j] = 1;
            } else {
                wcard_bin[i][j] = 0;
            }
            wcard[i] += wcard_bin[i][j] * pow(2, 7 - j);
        }
    }

    // Generate net,bcast and wcard in one array[4N,4B,4W]
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            net_bcast[i] += (ip_bin[i][j] * ip_bin[i + 4][j]) * pow(2, 7 - j);
        }
    }
    for (int i = 0; i < 4; i++) {
        net_bcast[i + 4] = net_bcast[i];
        for (int j = 0; j < 8; j++) {
            net_bcast[i + 4] += (wcard_bin[i][j] * pow(2, 7 - j));
        }
        net_bcast[i + 8] = wcard[i];
    }
    return net_bcast;
}

// Functions of print first part of result
inline void print_p1(int *ip_addr_mask)
{
    // Define variables
    int i;

    // Print to user
    cout << "IP address: ";
    for (i = 0; i < 3; i++) {
        cout << ip_addr_mask[i] << ".";
    }
    cout << ip_addr_mask[i] << endl;
    cout << "Netmask:    ";
    for (i = 4; i < 7; i++) {
        cout << ip_addr_mask[i] << ".";
    }
    cout << ip_addr_mask[i] << endl;
}

// Functions of print second part of result
inline void print_p2(int *net_bcast)
{
    // Define variables
    int i;
    double addrs = 1;

    // Print to user
    cout << "Wildcard:   ";
    for (i = 8; i < 11; i++) {
        cout << net_bcast[i] << ".";
    }
    cout << net_bcast[i] << endl;
    cout << "Network:    ";
    for (i = 0; i < 3; i++) {
        cout << net_bcast[i] << ".";
    }
    cout << net_bcast[i] << endl;
    cout << "Broadcast:  ";
    for (i = 4; i < 7; i++) {
        cout << net_bcast[i] << ".";
    }
    cout << net_bcast[i] << endl;
    cout << "Net class:  ";
    if (net_bcast[0] == 0) {
        cout << "Reserved (0.0.0.0 - 0.255.255.255)" << endl;
    } else if (net_bcast[0] > 1 && net_bcast[0] <= 126) {
        cout << "A (1.0.0.0 - 126.255.255.255)" << endl;
    } else if (net_bcast[0] == 127) {
        cout << "Reserved (127.0.0.0 - 127.255.255.255)" << endl;
    } else if (net_bcast[0] >= 128 && net_bcast[0] <= 191) {
        cout << "B (128.0.0.0 - 191.255.255.255)" << endl;
    } else if (net_bcast[0] > 191 && net_bcast[0] <= 223) {
        cout << "C (192.0.0.0 - 239.255.255.255)" << endl;
    } else if (net_bcast[0] > 223 && net_bcast[0] <= 239) {
        cout << "D (224.0.0.0 - 239.255.255.255)" << endl;
    } else {
        cout << "E (240.0.0.0 - 255.255.255.255)" << endl;
    }
    cout << "Addresses:  ";
    for (i = 8; i < 12; i++) {
        addrs *= (net_bcast[i] + 1);
    }
    cout << addrs << endl;
    cout << "Hosts:      ";
    if (addrs == 1) {
        cout << "1" << endl;
    } else if (addrs == 2) {
        cout << "2" << endl;
    } else {
        cout << (addrs - 2) << endl;
    }
}
