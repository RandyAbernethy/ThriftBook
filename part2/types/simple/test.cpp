// Simple Apache Thrift User Defined Type Example

#include <iostream>
#include <iomanip>
#include <boost/shared_ptr.hpp>

struct vs {
   int i;
   double d;
};

void test(const vs * p) {
   std::cout << p->i << std::endl;
}

int main(int argc, char *argv[]) {
    boost::shared_ptr<vs> spv(new vs);
    spv->i = 42;
    test(spv.get());
}
