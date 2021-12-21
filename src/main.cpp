#include "waterfilling.h"
#include "generator.h"
#include "gnuplot-iostream.h"

using namespace wf;

int main() {
    Vec alpha {0.12, 0.53, 0.134, 0.6};
    Vec x = WaterFilling::optimize(alpha);
    print(alpha);
    print(x);

	Generator generator;
    Vec random = generator.normal(10, 2, 1);
	print(random);

    return 0;
}
