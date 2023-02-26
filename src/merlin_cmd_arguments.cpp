#include <merlin_cmd_arguments.hpp>

#include <stdexcept>

namespace merl
{
    cmd_arguments::cmd_arguments(int argc, char * argv[]) : cmd_(argv[0])
    {
        for(int i = 1; i < argc; ++i)
        {
            if(argv[i][0] == '-')
            {
                std::string arg(argv[i]);
                std::size_t it = arg.find("=");

                if(it == std::string::npos)
                    opts_[arg] = {};
                else
                    opts_[arg.substr(0, it)] = arg.substr(it+1);
            }
            else
            {
                data_.emplace_back(argv[i]);
            }
        }
    }

    const std::string & cmd_arguments::command() const
    {
        return cmd_;
    }
            
    bool cmd_arguments::has_option(const std::string & option) const
    {
        return opts_.find(option) != opts_.end();
    }
    std::string cmd_arguments::option_value(const std::string & option) const
    {
        auto it = opts_.find(option);
        if(it == opts_.cend())
            throw std::invalid_argument("In merl::cmd_arguments::option_value(): The option \"" + option + "\" doesn't exist.");

        return it->second;
    }
    
    bool cmd_arguments::has_data() const
    {
        return !data_.empty();
    }
    const std::vector<std::string> & cmd_arguments::data() const
    {
        return data_;
    }
}