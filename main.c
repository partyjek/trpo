#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int *localize(string ip_net)
{
    int ip_addr_ar[4],ip_mask,ip_mask_dec,ip_mask_ar[4],i;
    string delim_addr = ".",ip_addr_str,ip_addr_dig;
    string delim_mask = "/",ip_mask_str,ip_mask_dig;
    int pos = ip_net.find(delim_mask);
    static int ip_addr_mask[8];

    //Split IP address and netmask
    ip_addr_dig = ip_net.substr(0,pos);
    ip_mask_dig = ip_net.substr(pos+1,ip_net.length());

    //Create empty addr and mask
    for(i = 0; i < 4; i++){
        ip_addr_ar[i] = 0;
        ip_mask_ar[i] = 0;
    }

    //Get correct IP address
    try {
        for (i = 0; i < 4; i++){
            ip_addr_ar[i] = stoi(ip_addr_dig.substr(0,ip_addr_dig.find(delim_addr)));
            ip_addr_dig.erase(0,ip_addr_dig.find(delim_addr)+1);
        }
    }
    catch(...){
        cout << "IP address contains illegal symbols" << endl;
        //return;
    }

    //Get correct mask
    try {
        ip_mask = stoi(ip_mask_dig);
    }
    catch(...){
        cout << "Net mask is not integer" << endl;
        //return;
    }
    if (ip_mask < 0 | ip_mask > 32){
        cout << "Net mask is not in range (0,32)" << endl;
        //return;
    }
    ip_mask_dec = 255 * (ip_mask/8);
    for (i = 0; i < ip_mask  - 8 * (ip_mask/8); i++){
        ip_mask_dec += pow(2,7-i);
    }
    i = 0;
    while (ip_mask_dec >= 256){
        ip_mask_ar[i] = 255;
        i++;
        ip_mask_dec -= 255;
    }
    ip_mask_ar[i] = ip_mask_dec;

    //Building output
    for (i = 0; i < 4; i++){
        ip_addr_mask[i] = ip_addr_ar[i];
        ip_addr_mask[i+4] = ip_mask_ar[i];
    }
    return ip_addr_mask;
}

int **dec2bin(int* ip){
    static int **ip_bin=new int*[8];
    for (int i=0; i < 8; i++)
        ip_bin[i]=new int[8];
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (ip[i] >= pow(2,7-j)){
                ip_bin[i][j] = 1;
                ip[i] -= pow(2,7-j);
            }
            else{
                ip_bin[i][j] = 0;
            }
        }
    }
    return ip_bin;
}

int main()
{
    string ip_net;
    cout << "Input IP/mask (ex. A-AAA.B-BBB.C-CCC.D-DDD/EE" << endl;
    cin>>ip_net;
    int* ip_addr_mask = localize(ip_net);
    int** ip_bin;
//    int  (*ip_bin)[8];
    ip_bin = dec2bin(ip_addr_mask);

//    for (int i = 0; i < 8; i++){
//        cout << ip[i] << endl;
//    }
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            cout << ip_bin[i][j];
        }
        cout << endl << endl;
    }
//    for (int i = 0; i < 8; i++){
//        for (int j = 0; j < 8; j++){
//            cout << ip_bin[i][j];
//        }
//        cout << endl << endl;
//    }

    return 0;
}
