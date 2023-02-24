#include <merlin_ini.hpp>

#include <merlin_utility.hpp>

#include <fstream>
#include <vector>

namespace merl
{
    ini::ini()
    {}
    ini::ini(const std::string & ini_file)
    {
        this->load(ini_file);
    }
    bool ini::load(const std::string & ini_file)
    {
        std::ifstream ifs(ini_file);
        if(!ifs)
        {
            error_message_ = "Could not open the file " + ini_file + " in read mode.";
            return false;
        }

        std::string line;
        std::size_t n {0}; // To keep track of the line number
        std::string current_group {};

        while(std::getline(ifs, line))
        {
            ++n;

            if(line.empty() || line[0] == ';')                                                                    // Empty line or comment filter
            {}
            else if(line.size() > 2 && line[0] == '[' && line[line.size()-1] == ']')                              // Group filter
            {
                current_group = trim<char>(line.substr(1, line.size()-2));
                data_[current_group] = {};
            }
            else if(line.size() >= 3 && line.find('=') == line.rfind('=') && line.find('=') != std::string::npos) // Key-value filter
            {
                if(!current_group.empty())
                {
                    std::vector<std::string> key_value_data = split<char, std::vector>(line, '=');
                    data_[current_group][trim<char>(key_value_data[0])] = trim<char>(key_value_data[1]);
                }
                else
                {
                    error_message_ = "At line " + std::to_string(n) + ": Key-value data must belong to a section.";
                    return false;
                }
            }
            else                                                                                                  // Invalid format
            {
                error_message_ = "Invalid format at line " + std::to_string(n) + ": Data are expected to be in INI format.";
                return false;
            }
        }

        ifs.close();
        return true;
    }
    bool ini::save(const std::string & ini_file)
    {
        std::ofstream ofs(ini_file);
        if(!ofs)
        {
            error_message_ = "Could not open the file " + ini_file + " in write mode.";
            return false;
        }
        
        for(const auto & [g, d] : data_)
        {
            ofs << '[' << g << ']' << '\n';
            for(const auto & [k, v] : d)
            {
                ofs << k << " = " << v << '\n';
            }
            ofs << '\n';
        }

        ofs.close();
        return true;
    }
    const std::string & ini::error_message() const
    {
        return error_message_;
    }
    std::unordered_map<std::string, std::string> & ini::operator[](const std::string & group)
    {
        return data_[group];
    }
    bool ini::contains(const std::string & group) const
    {
        return data_.find(group) != data_.cend();
    }
    bool ini::contains(const std::string & group, const std::string & key) const
    {
        return this->contains(group) && data_.at(group).find(key) != data_.at(group).cend();
    }
}