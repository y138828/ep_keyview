#ifndef config_manager_header
#define config_manager_header

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <memory>
#include <atomic>
#include <list>

#include <boost/program_options.hpp>

class config_manager{
    private:
        config_manager();
        ~config_manager();
    private:
        boost::program_options::options_description command_generic;
        boost::program_options::options_description command_file;
        std::string default_config_file;

    public:
        bool parser_from_command_line(int argc,char *argv[]);
        bool parser_from_config_file(const std::string& file);
        bool parser_From_env();

    public:
        static config_manager* shared_instance();
};



#endif