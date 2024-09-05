#include <iostream>
#include <cstdlib>
#include <string>
#include <thread>
#include <chrono>

#include "comm/tcp_connector.hpp"
#include "hako_capi.h"
#include "modules/hako_ucw.hpp"
#include "utils/hako_params.hpp"
#include "config/drone_config.hpp"
#ifndef WIN32
#include "modules/hako_bypass.hpp"
#endif
class DroneConfigManager drone_config_manager;

int main(int argc, char* argv[]) 
{
    const char* value = std::getenv("HAKO_MASTER_DISABLE");
    bool enable_master = true;
    if (value != nullptr) {
        std::string valueStr(value);
        if (valueStr == "true") {
            std::cout << "hakoniwa master is disabled" << std::endl;
            enable_master = false;
        } else {
            std::cout << "hakoniwa master is enabled" << std::endl;
        }
    } else {
        std::cout << "hakoniwa master is enabled" << std::endl;
    }

    hako_param_env_init();

    //hako::px4::comm::ICommIO *comm_io  = nullptr;
    
    // hako_ucw_main を別スレッドで実行し，hako-cmd start を実行する
    //std::thread thd(hako_ucw_main, enable_master);
    //thd.join();
    //printf("***asset start\n");
    //system("hako-cmd start");

    hako_ucw_main(enable_master);
    
#ifndef WIN32
#endif
    //comm_io->close();
    return 0;
}
