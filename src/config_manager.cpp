#include "config_manager.hpp"

static config_manager* g_instance = 0;
config_manager* config_manager::config_manager::shared_instance()
{
    if (!g_instance)
    {
        g_instance = new config_manager();
    }
    return g_instance;
}
config_manager::config_manager():command_generic("generic options"),command_file("config file options"){
    
}
config_manager::~config_manager(){

}
bool config_manager::parser_from_command_line(int argc,char *argv[]){
    return true;
}
bool config_manager::parser_from_config_file(const std::string& file){
    return true;
}
bool config_manager::parser_From_env(){
    return true;
}

