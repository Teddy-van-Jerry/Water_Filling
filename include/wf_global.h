/**
 * @file wf_global.h
 * @author Teddy van Jerry (me@teddy-van-Jerry.org)
 * @brief The global include file for Water Filling
 * @version 0.1
 * @date 2022-01-01
 * 
 * @copyright Copyright (c) 2022 Teddy van Jerry
 * 
 */

#ifndef WF_GLOBAL_H
#define WF_GLOBAL_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

/**
 * @brief Water Filling namespace
 * 
 */
namespace wf {

    /// Number Vector
    using Vec = std::vector<double>;

    /// String
    using Str = std::string;

    /// Message
    using Msg = Str;

    /// Messages
    using Msgs = std::vector<Msg>;

    constexpr int const DEFAULT_ITER_MAX = 1000; ///< default max iterations
    constexpr double const DEFAULT_PRECISION = 6; ///< default precision in optimization

    /**
     * @brief Print the data vector.
     * 
     * @param v vector
     * @param s dividing string
     * @param end end string
     */
    void print(const Vec& v, const wf::Str& s = ", ", const wf::Str& end = "\n");

    /**
     * @brief Get the file extension name of a file name.
     * 
     * @param s file name
     * @return extension name
     */
    Str fileExt(const Str& s);

    /**
     * @brief Read data vector from file.
     * 
     * @param file file name
     * @param ok ptr of status
     * @return the data vector
     */
    Vec readFile(const Str& file, bool* ok = nullptr);

    /**
     * @brief Save the data vector to file.
     * 
     * @param file file name
     * @param data data vector
     */
    bool saveAs(const Str& file, const Vec& data);

    /**
     * @brief Convert the string to all lowercases.
     * 
     * @param s string
     * @return the converted string
     */
    Str toLower(const Str& s);

}

#endif // WF_GLOBAL_H
