#include <iostream>
#include <string>
#include <cmath>
#include "functions.cpp"

//Use "standart" namespace (string,cout,cin etc.)
using namespace std;

//Main function
int main(){

    //Define variables
    int i;
    double addrs = 1;
    string ip_net;
    int* ip_addr_mask;
    int* net_bcast;
    int** ip_bin;

    //Input IP address and Netmask
    cout << "Input IP/mask (ex. A-AAA.B-BBB.C-CCC.D-DDD/EE or A-AAA.B-BBB.C-CCC.D-DDD/xxx.xxx.xxx.xxx" << endl;
    cin >> ip_net;
    cout << endl;

    //Localize IP/mask with many types of input
    if ((ip_net.substr(ip_net.find('/')+1,ip_net.length())).length() <= 2){
        ip_addr_mask = gen_ip_array(ip_net);
    }
    else{
        ip_net = localize(ip_net);
        ip_addr_mask = gen_ip_array(ip_net);
    }

    //Print to user
    cout << "You input:  " << ip_net << endl;
    cout << "IP address: ";
    for (i = 0; i < 3; i++){
        cout << ip_addr_mask[i] << ".";
    }
    cout <<ip_addr_mask[i] << endl;
    cout << "Netmask:    ";
    for (i = 4; i < 7; i++){
        cout <<ip_addr_mask[i] << ".";
    }
    cout <<ip_addr_mask[i] << endl;

    //Generate binary IP and Netmask (array[[A],[B],[C],[D],[M1],[M2],[M3],[M4]])
    ip_bin = dec2bin(ip_addr_mask);

    //Find Net adress and broadcast
    net_bcast = bin2addr(ip_bin);

    //Print to user
    cout << "Wildcard:   ";
    for (i = 8; i < 11; i++){
        cout << net_bcast[i] << ".";
    }
    cout <<net_bcast[i] << endl;
    cout << "Network:    ";
    for (i = 0; i < 3; i++){
        cout << net_bcast[i] << ".";
    }
    cout <<net_bcast[i] << endl;
    cout << "Broadcast:  ";
    for (i = 4; i < 7; i++){
        cout << net_bcast[i] << ".";
    }
    cout <<net_bcast[i] << endl;
    cout << "Net class:  ";
    if (net_bcast[0] == 0){
        cout << "Reserved (0.0.0.0 - 0.255.255.255)" << endl;
    }
    else if (net_bcast[0] > 1 & net_bcast[0] <= 126){
        cout << "A (1.0.0.0 - 126.255.255.255)" << endl;
    }
    else if (net_bcast[0] == 127){
        cout << "Reserved (127.0.0.0 - 127.255.255.255)" << endl;
    }
    else if (net_bcast[0] >= 128 & net_bcast[0] <= 191){
        cout << "B (128.0.0.0 - 191.255.255.255)" << endl;
    }
    else if (net_bcast[0] > 191 & net_bcast[0] <= 223){
        cout << "C (192.0.0.0 - 239.255.255.255)" << endl;
    }
    else if (net_bcast[0] > 223 & net_bcast[0] <= 239){
        cout << "D (224.0.0.0 - 239.255.255.255)" << endl;
    }
    else{
        cout << "E (240.0.0.0 - 255.255.255.255)" << endl;
    }
    cout << "Addresses:  ";
    for (i = 8; i < 12; i++){
        addrs *= (net_bcast[i] + 1);
    }
    cout << addrs << endl;
    cout << "Hosts:      ";
    if (addrs == 1){
        cout << "1" << endl;
    }
    else if (addrs == 2){
        cout << "2" << endl;
    }
    else{
        cout << (addrs - 2) << endl;
    }

    //Delete all arrays
    delete [] ip_addr_mask;
    delete [] net_bcast;
    for (int i = 0; i < 8; i++){
        delete [] ip_bin[i];
    }
    delete[] ip_bin;

    return 0;
}
