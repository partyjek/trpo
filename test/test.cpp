#include <ctest.h>
#include <functions.cpp>
#include <iostream>

using namespace std;

CTEST(localize_ip_net, mask_dec_full_true)
{
    // Given
    const string ip = "10.2.128.3/255.255.255.0";

    // When
    const string get_func = localize(ip);

    // Then
    const string expected = "10.2.128.3/24";

    // Compare
    bool result;
    if (get_func == expected)
        result = true;
    else
        result = false;
    ASSERT_TRUE(result);
}

CTEST(localize_ip_net, mask_dec_full_false)
{
    // Given
    const string ip = "10.2.128.3/255.255.255.0";

    // When
    const string get_func = localize(ip);

    // Then
    const string expected = "10.2.128.3/255.255.255.0";

    // Compare
    bool result;
    if (get_func != expected)
        result = true;
    else
        result = false;
    ASSERT_TRUE(result);
}

CTEST(gen_ip_array, gen_ip)
{
    // Given
    const int *get_func = new int[8];
    const string ip_net = "172.16.64.1/16";

    // When
    get_func = gen_ip_array(ip_net);

    // Then
    const int expected[4] = {172, 16, 64, 1};

    // Compare
    bool result = true;
    for (int i = 0; i <= 3; i++) {
        if (get_func[i] != expected[i])
            result = false;
    }
    ASSERT_TRUE(result);
}

CTEST(gen_ip_array, gen_mask)
{
    // Given
    const int *get_func = new int[8];
    const string ip_net = "172.16.64.1/16";

    // When
    get_func = gen_ip_array(ip_net);

    // Then
    const int expected[4] = {255, 255, 0, 0};

    // Compare
    bool result = true;
    for (int i = 0; i <= 3; i++) {
        if (get_func[i + 4] != expected[i])
            result = false;
    }
    ASSERT_TRUE(result);
}

CTEST(gen_ip_array, gen_false)
{
    // Given
    const int *get_func = new int[8];
    const string ip_net = "172.16.64.1/16";

    // When
    get_func = gen_ip_array(ip_net);

    // Then
    const int expected[8] = {255, 0, 255, 0, 255, 0, 255, 0};

    // Compare
    bool result = true;
    for (int i = 0; i <= 7; i++) {
        if (get_func[i] != expected[i])
            result = false;
    }
    ASSERT_FALSE(result);
}

CTEST(dec2bin, A_IP2bin)
{
    // Given
    int **get_func;
    int ip_net[8] = {10, 10, 10, 10, 0, 0, 0, 0};

    // When
    get_func = dec2bin(ip_net);

    // Then
    const int expected[8] = {0, 0, 0, 0, 1, 0, 1, 0};

    // Compare
    bool result = true;
    for (int i = 0; i <= 3; i++) {
        for (int j = 0; j <= 7; j++) {
            if (get_func[i][j] != expected[j])
                result = false;
        }
    }
    ASSERT_TRUE(result);
}

CTEST(dec2bin, B_IP2bin)
{
    // Given
    int **get_func;
    int ip_net[8] = {172, 172, 172, 172, 0, 0, 0, 0};

    // When
    get_func = dec2bin(ip_net);

    // Then
    const int expected[8] = {1, 0, 1, 0, 1, 1, 0, 0};

    // Compare
    bool result = true;
    for (int i = 0; i <= 3; i++) {
        for (int j = 0; j <= 7; j++) {
            if (get_func[i][j] != expected[j])
                result = false;
        }
    }
    ASSERT_TRUE(result);
}

CTEST(dec2bin, C_IP2bin)
{
    // Given
    int **get_func;
    int ip_net[8] = {192, 192, 192, 192, 0, 0, 0, 0};

    // When
    get_func = dec2bin(ip_net);

    // Then
    const int expected[8] = {1, 1, 0, 0, 0, 0, 0, 0};

    // Compare
    bool result = true;
    for (int i = 0; i <= 3; i++) {
        for (int j = 0; j <= 7; j++) {
            if (get_func[i][j] != expected[j])
                result = false;
        }
    }
    ASSERT_TRUE(result);
}

CTEST(dec2bin, D_IP2bin)
{
    // Given
    int **get_func;
    int ip_net[8] = {224, 224, 224, 224, 0, 0, 0, 0};

    // When
    get_func = dec2bin(ip_net);

    // Then
    const int expected[8] = {1, 1, 1, 0, 0, 0, 0, 0};

    // Compare
    bool result = true;
    for (int i = 0; i <= 3; i++) {
        for (int j = 0; j <= 7; j++) {
            if (get_func[i][j] != expected[j])
                result = false;
        }
    }
    ASSERT_TRUE(result);
}

CTEST(dec2bin, ip2bin_false)
{
    // Given
    int **get_func;
    int ip_net[8] = {10, 172, 192, 224, 0, 0, 0, 0};

    // When
    get_func = dec2bin(ip_net);

    // Then
    const int expected[8] = {1, 1, 1, 0, 0, 0, 0, 0};

    // Compare
    bool result = true;
    for (int i = 0; i <= 3; i++) {
        for (int j = 0; j <= 7; j++) {
            if (get_func[i][j] != expected[j])
                result = false;
        }
    }
    ASSERT_FALSE(result);
}

CTEST(dec2bin, zero_mask2bin)
{
    // Given
    int **get_func;
    int ip_net[8] = {192, 168, 0, 1, 0, 0, 0, 0};

    // When
    get_func = dec2bin(ip_net);

    // Then
    const int expected = 0;

    // Compare
    bool result = true;
    for (int i = 4; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            if (get_func[i][j] != expected)
                result = false;
        }
    }
    ASSERT_TRUE(result);
}

CTEST(dec2bin, max_mask2bin)
{
    // Given
    int **get_func;
    int ip_net[8] = {192, 168, 0, 1, 255, 255, 255, 255};

    // When
    get_func = dec2bin(ip_net);

    // Then
    const int expected = 1;

    // Compare
    bool result = true;
    for (int i = 4; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            if (get_func[i][j] != expected)
                result = false;
        }
    }
    ASSERT_TRUE(result);
}

CTEST(dec2bin, half_mask2bin_false)
{
    // Given
    int **get_func;
    int ip_net[8] = {192, 168, 0, 1, 255, 255, 0, 0};

    // When
    get_func = dec2bin(ip_net);

    // Then
    const int expected = 0;

    // Compare
    bool result = true;
    for (int i = 4; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            if (get_func[i][j] != expected)
                result = false;
        }
    }
    ASSERT_FALSE(result);
}

CTEST(bin2addr, zero_bin2ip)
{
    // Given
    int *get_func;
    int **ip_bin = new int *[8];
    for (int i = 0; i <= 7; i++)
        ip_bin[i] = new int[8];
    for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            ip_bin[i][j] = 0;
        }
    }

    // When
    get_func = bin2addr(ip_bin);

    // Then
    const int expected = 0;

    // Compare
    bool result = true;
    for (int i = 0; i <= 3; i++) {
        if (get_func[i] != expected)
            result = false;
    }
    ASSERT_TRUE(result);
}

CTEST(bin2addr, ip_bin2ip)
{
    // Given
    int *get_func;
    int **ip_bin = new int *[8];
    for (int i = 0; i <= 7; i++)
        ip_bin[i] = new int[8];
    for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            if (j == 0 || j == 1)
                ip_bin[i][j] = 1;
            else
                ip_bin[i][j] = 0;
        }
    }

    // When
    get_func = bin2addr(ip_bin);

    // Then
    const int expected = 192;

    // Compare
    bool result = true;
    for (int i = 0; i <= 3; i++) {
        if (get_func[i] != expected)
            result = false;
    }
    ASSERT_TRUE(result);
}

CTEST(bin2addr, max_bin2ip)
{
    // Given
    int *get_func;
    int **ip_bin = new int *[8];
    for (int i = 0; i <= 7; i++)
        ip_bin[i] = new int[8];
    for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            ip_bin[i][j] = 1;
        }
    }

    // When
    get_func = bin2addr(ip_bin);

    // Then
    const int expected = 255;

    // Compare
    bool result = true;
    for (int i = 0; i <= 3; i++) {
        if (get_func[i] != expected)
            result = false;
    }
    ASSERT_TRUE(result);
}

CTEST(bin2addr, zero_bin2wcard)
{
    // Given
    int *get_func;
    int **ip_bin = new int *[8];
    for (int i = 0; i <= 7; i++)
        ip_bin[i] = new int[8];
    for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            ip_bin[i][j] = 0;
        }
    }

    // When
    get_func = bin2addr(ip_bin);

    // Then
    const int expected = 255;

    // Compare
    bool result = true;
    for (int i = 0; i <= 3; i++) {
        if (get_func[i + 8] != expected)
            result = false;
    }
    ASSERT_TRUE(result);
}

CTEST(bin2addr, ip_bin2wcard)
{
    // Given
    int *get_func;
    int **ip_bin = new int *[8];
    for (int i = 0; i <= 7; i++)
        ip_bin[i] = new int[8];
    for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            if (j == 0 || j == 1)
                ip_bin[i][j] = 1;
            else
                ip_bin[i][j] = 0;
        }
    }

    // When
    get_func = bin2addr(ip_bin);

    // Then
    const int expected = 255 - 192;

    // Compare
    bool result = true;
    for (int i = 0; i <= 3; i++) {
        if (get_func[i + 8] != expected)
            result = false;
    }
    ASSERT_TRUE(result);
}

CTEST(bin2addr, max_bin2wcard)
{
    // Given
    int *get_func;
    int **ip_bin = new int *[8];
    for (int i = 0; i <= 7; i++)
        ip_bin[i] = new int[8];
    for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            ip_bin[i][j] = 1;
        }
    }

    // When
    get_func = bin2addr(ip_bin);

    // Then
    const int expected = 0;

    // Compare
    bool result = true;
    for (int i = 0; i <= 3; i++) {
        if (get_func[i + 8] != expected)
            result = false;
    }
    ASSERT_TRUE(result);
}

CTEST(bin2addr, bin2ip_false)
{
    // Given
    int *get_func;
    int **ip_bin = new int *[8];
    for (int i = 0; i <= 7; i++)
        ip_bin[i] = new int[8];
    for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            ip_bin[i][j] = 1;
        }
    }

    // When
    get_func = bin2addr(ip_bin);

    // Then
    const int expected = 1;

    // Compare
    bool result = true;
    for (int i = 0; i <= 3; i++) {
        if (get_func[8] != expected)
            result = false;
    }
    ASSERT_FALSE(result);
}

CTEST(bin2addr, bin2wcard_false)
{
    // Given
    int *get_func;
    int **ip_bin = new int *[8];
    for (int i = 0; i <= 7; i++)
        ip_bin[i] = new int[8];
    for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            ip_bin[i][j] = 1;
        }
    }

    // When
    get_func = bin2addr(ip_bin);

    // Then
    const int expected = 1;

    // Compare
    bool result = true;
    for (int i = 0; i <= 3; i++) {
        if (get_func[i + 8] != expected)
            result = false;
    }
    ASSERT_FALSE(result);
}
