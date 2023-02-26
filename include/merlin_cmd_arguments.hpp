#ifndef MERLIN_CMD_ARGUMENTS_HPP
#define MERLIN_CMD_ARGUMENTS_HPP

#include <string>
#include <unordered_map>
#include <vector>

namespace merl
{
    class cmd_arguments
    {
        private:
            std::string cmd_;
            std::unordered_map<std::string, std::string> opts_;
            std::vector<std::string> data_;

        public:
            cmd_arguments() = delete;
            cmd_arguments(int argc, char * argv[]);

            const std::string & command() const;
            
            bool has_option(const std::string & option) const;
            std::string option_value(const std::string & option) const;
            
            bool has_data() const;
            const std::vector<std::string> & data() const;
    };
}

#endif