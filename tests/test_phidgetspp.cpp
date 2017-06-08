#include <phidgetspp/phidgetspp.hpp>
#include <thread>
#include <chrono>
int main()
{
    using namespace std::literals;
    ppp::phidgets_manager m;

    std::this_thread::sleep_for(5s);
}
