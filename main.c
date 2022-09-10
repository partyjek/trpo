#include <iostream>
#include <string>
#include <cmath>

using namespace std;

void localize(string ip_net)
{
    int ip_addr_ar[4],ip_mask,ip_mask_dec,ip_mask_ar[4],i;
    string delim_addr = ".",ip_addr_str,ip_addr_dig;
    string delim_mask = "/",ip_mask_str,ip_mask_dig;
    int pos = ip_net.find(delim_mask);

    //Split IP address and netmask
    ip_addr_dig = ip_net.substr(0,pos);
    ip_mask_dig = ip_net.substr(pos+1,ip_net.length());
    cout << ip_addr_dig << endl;
    cout << ip_mask_dig << endl;

    //Create empty addr and mask
    for(i = 0; i < 4; i++){
        ip_addr_ar[i] = 0;
        ip_mask_ar[i] = 0;
    }

    //Get correct IP address
    try {
        for (i = 0; i < 4; i++){
            ip_addr_ar[i] = stoi(ip_addr_dig.substr(0,ip_addr_dig.find(delim_addr)));
            ip_addr_dig.erase(0,ip_addr_str.find(delim_addr)+1);
        }
    }
    catch(...){
        cout << "IP address contains illegal symbols" << endl;
        return;
    }

    //Get correct mask
    try {
        ip_mask = stoi(ip_mask_dig);
    }
    catch(...){
        cout << "Net mask is not integer" << endl;
        return;
    }
    if (ip_mask < 0 | ip_mask > 32){
        cout << "Net mask is not in range (0,32)" << endl;
        return;
    }
    ip_mask_dec = 255 * (ip_mask/8);
//    cout << "До сложения " << ip_mask_dec << endl;
    for (i = 0; i < ip_mask  - 8 * (ip_mask/8); i++){
        ip_mask_dec += pow(2,7-i);
//        cout << "Сложение " << pow(2,7-i) << " " << ip_mask_dec << endl;
    }
//    cout << "После сложения " << ip_mask_dec << endl << endl;
    i = 0;
    while (ip_mask_dec >= 256){
        ip_mask_ar[i] = 255;
        i++;
        ip_mask_dec -= 255;
    }
    ip_mask_ar[i] = ip_mask_dec;

    for(i = 0; i < 4; i++){
        ip_addr_str += to_string(ip_addr_ar[i]);
        if (i != 3){
            ip_addr_str += delim_addr;
        }
    };
    for(i = 0; i < 4; i++){
        ip_mask_str += to_string(ip_mask_ar[i]);
        if (i != 3){
            ip_mask_str += delim_addr;
        }
    };
    cout << ip_addr_str << endl;
    cout << ip_mask_str << endl;
}

void get_net()
{
}

int main()
{
    string ip_net;
    cin>>ip_net;
    localize(ip_net);

    return 0;
}
