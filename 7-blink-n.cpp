#include <bcm2835.h>
#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv) {
    if (!bcm2835_init()) {
        return 1;
    }

    if (argc < 2) {
        cerr << "Usage: ./a.out PIN1 [PIN2 [PIN3 ...]]\n";
        return 1;
    }

    int mask = 0;

    for (int c = 0; c < argc - 1; c++) {
        int n = atoi(argv[c + 1]);

        if (n < 32 || n > 45) {
            cerr << "Pin number must be between 32 and 45\n";
            return 1;
        }

        bcm2835_gpio_fsel(n, BCM2835_GPIO_FSEL_OUTP);
        mask |= 1 << (n - 32);
    }


    uint32_t* gpioBASE = bcm2835_regbase(BCM2835_REGBASE_GPIO);

    int p = 0;
    while(1) {
        bcm2835_peri_write(gpioBASE + BCM2835_GPSET1 / 4, mask);
        bcm2835_delay(500);
        bcm2835_peri_write(gpioBASE + BCM2835_GPCLR1 / 4, mask);
        bcm2835_delay(500);
    }

    return 0;
}
