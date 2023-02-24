#ifndef MERLIN_INI_HPP
#define MERLIN_INI_HPP

/*!
 * \file merlin_ini.hpp
 * \brief An INI files (.ini) parser implementation.
 * \author Raphaël Lefèvre
*/

#include <unordered_map>

/*!
 * \namespace merl
 * \brief Merlin namespace.
*/
namespace merl
{
    /*!
     * \class ini
     * \brief A class which can hold, load and save data under the INI format.
    */
    class ini
    {
        private:
            std::unordered_map<std::string, std::unordered_map<std::string, std::string>> data_;
            std::string error_message_;

        public:
            /*!
             * \brief Default constructor.
             * \details Create an empty Ini object.
            */
            ini();
            /*!
             * \brief Constructor.
             * \param[in] ini_file The file to load the data from
            */
            ini(const std::string & ini_file);

            /*!
             * \brief Load data from an INI file.
             * \param[in] ini_file The file to load the data from
             * \return Whether or not the file could be opened
            */
            bool load(const std::string & ini_file);
            /*!
             * \brief Save data into an INI file.
             * \param[in] ini_file The file to write the data into
             * \return Whether or not the file could be opened
            */
            bool save(const std::string & ini_file);

            /*!
             * \brief Get the last error message (if any)
             * \return A constant reference to the error message string describing the error that last occured (empty message if no error)
            */
            const std::string & error_message() const;
            /*!
             * \brief Overload of subscript operator for data access.
             * \param[in] group The INI group under which the data are requested
             * \return A reference to the underlying data corresponding to the given group
             * \note If the given group does not exist, it will be automatically created. In this case, the underlying data (which will be returned) will be value-initialized.
            */
            std::unordered_map<std::string, std::string> & operator[](const std::string & group);

            /*!
             * \brief Check if a group does exist in the INI data.
             * \param[in] group The group we want to look up
             * \return Whether or not the given group exists
            */
            bool contains(const std::string & group) const;
            /*!
             * \brief Check if a parameter does exist for a given group in the INI data.
             * \param[in] group The group holding the parameter
             * \param[in] key The parameter we want to look up
             * \return Whether or not the given (group, parameter) exists
            */
            bool contains(const std::string & group, const std::string & key) const;
    };
}

#endif