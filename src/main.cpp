#include "waterfilling.h"

using namespace wf;

int main() {
    Vec alpha {0.12, 0.53, 0.134, 0.6};
    Vec x = WaterFilling::optimize(alpha);
    print(alpha);
    print(x);
    return 0;
}
