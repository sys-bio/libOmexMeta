/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Christophe Meessen
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef URL_HPP
#define URL_HPP

#include <utility>
#include <vector>
#include <utility>
#include <stdexcept>
#include <cstdint>
#include <ostream>
#include <utility>

namespace semsim {
    class Uri {
    public:
        // Exception thut may be thrown when decoding an URL or an assigning value
        class parse_error : public std::invalid_argument {
        public:
            explicit parse_error(const std::string &reason) : std::invalid_argument(reason) {}
        };

        // Exception that may be thrown when string an URL
        class str_error : public std::runtime_error {
        public:
            explicit str_error(const std::string &reason) : std::runtime_error(reason) {}
        };

                // Default constructor
        Uri() : m_parse(true), m_built(true), m_ip_v(-1) {}

        // Copy initializer constructor
        Uri(const Uri &url) : m_ip_v(-1) { assign(url); }

        // Move constructor
        Uri(Uri &&url) noexcept : m_ip_v(-1)  {
            assign(std::move(url));
        }

        // Construct Uri with the given string
        explicit Uri(std::string url_str) : m_url(std::move(url_str)), m_parse(false), m_built(false), m_ip_v(-1) {}

        // Assign the given URL string
        Uri &operator=(std::string &url_str) {

            return str(url_str);
        }

        // Assign the given Uri object
        Uri &operator=(const Uri &url) {
            assign(url);
            return *this;
        }

        // Move the given Uri object
        Uri &operator=(Uri &&url) {
            assign(std::move(url));
            return *this;
        }

        bool operator==(const Uri &rhs) const;

        bool operator!=(const Uri &rhs) const;

        // Clear the Uri object
        Uri &clear();

        // str Uri if needed and return it as string
        std::string str() const {
            if (!m_built) str_url();
            return m_url;
        }

        // Set the Uri to the given string. All fields are overwritten
        Uri &str(std::string &url_str) {
            m_url = url_str;
            m_built = m_parse = false;
            return *this;
        }

        // Get scheme
         std::string &scheme() const {
            lazy_parse();
            return m_scheme;
        }

        // Set scheme
        Uri &scheme(const std::string &s);

        // Get user info
         std::string &user_info()  {
            lazy_parse();
            return m_user;
        }

        // Set user info
        Uri &user_info(const std::string &s);

        // Get host
         std::string &host()  {
            lazy_parse();
            return m_host;
        }

        // Set host
        Uri &host(const std::string &h, uint8_t ip_v = 0);

        // Get host IP version: 0=name, 4=IPv4, 6=IPv6, -1=undefined
        std::int8_t ip_version()  {
            lazy_parse();
            return m_ip_v;
        }

        // Get port
         std::string &port()  {
            lazy_parse();
            return m_port;
        }

        // Set Port given as string
        Uri &port(const std::string &str);

        // Set port given as a 16bit unsigned integer
        Uri &port(std::uint16_t num) { return port(std::to_string(num)); }

        // Get path
         std::string &path()  {
            lazy_parse();
            return m_path;
        }

        // Set path
        Uri &path(const std::string &str);

        class KeyVal {
        public:
            // Default constructor
            KeyVal() = default;

            // Construct with provided Key and Value strings
            KeyVal(std::string key,  std::string &val) : m_key(std::move(key)), m_val(val) {}

            // Construct with provided Key string, val will be empty
            KeyVal(std::string key) : m_key(std::move(key)) {}

            bool operator==(const KeyVal &rhs) const {
                return m_key == rhs.m_key &&
                       m_val == rhs.m_val;
            }

            bool operator!=(const KeyVal &rhs) const {
                return !(rhs == *this);
            }
            // Equality test operator
//            bool operator==(const KeyVal &q)  { return m_key == q.m_key && m_val == q.m_val; }

            // Swap this with q
            void swap(KeyVal &q) {
                std::swap(m_key, q.m_key);
                std::swap(m_val, q.m_val);
            }

            // Get key
             std::string &key()  { return m_key; }

            // Set key
            void key(const std::string &k) { m_key = k; }

            // Get value
             std::string &val()  { return m_val; }

            // Set value
            void val(const std::string &v) { m_val = v; }

            // Output key value pair
            friend std::ostream &operator<<(std::ostream &o, const KeyVal &kv) {
                o << "<key(" << kv.m_key << ") val(" << kv.m_val << ")> ";
                return o;
            }

        private:
            std::string m_key;
            std::string m_val;
        };

        // Define Query as vector of Key Value pairs
        typedef std::vector<KeyVal> Query;

        // Get a reference to the query vector for read only access
         Query &query()  {
            lazy_parse();
            return m_query;
        }

        // Get a reference to a specific Key Value pair in the query vector for read only access
         KeyVal &query(size_t i)  {
            lazy_parse();
            if (i >= m_query.size())
                throw std::out_of_range("Invalid Uri query index (" + std::to_string(i) + ")");
            return m_query[i];
        }

        // Get a reference to the query vector for a writable access
        Query &set_query() {
            lazy_parse();
            m_built = false;
            return m_query;
        }

        // Get a reference to specific Key Value pair in the query vector for a writable access
        KeyVal &set_query(size_t i) {
            lazy_parse();
            if (i >= m_query.size())
                throw std::out_of_range("Invalid Uri query index (" + std::to_string(i) + ")");
            m_built = false;
            return m_query[i];
        }

        // Set the query vector to the Query vector q
        Uri &set_query(Query &q) {
            lazy_parse();
            if (q != m_query) {
                m_query = q;
                m_built = false;
            }
            return *this;
        }

        // Append KeyVal kv to the query
        Uri &add_query(KeyVal &kv) {
            lazy_parse();
            m_built = false;
            m_query.push_back(kv);
            return *this;
        }

        // Append key val pair to the query
        Uri &add_query(std::string &key, std::string &val) {
            lazy_parse();
            m_built = false;
            m_query.emplace_back(key, val);
            return *this;
        }

        // Append key with empty val to the query
        Uri &add_query(std::string &key) {
            lazy_parse();
            m_built = false;
            m_query.emplace_back(key);
            return *this;
        }

        // Get the fragment
         std::string &fragment()  {
            lazy_parse();
            return m_fragment;
        }

        // Set the fragment
        Uri &fragment(const std::string &f);

        // Output
        std::ostream &output(std::ostream &o) const;

        friend std::ostream &operator<<(std::ostream &os, const Uri &uri);

        /*
         * return just the last part of the url, i.e.
         * after the last "/" but before a fragment
         * if one exists.
         */
        std::string end();

        /*
         * return the url up until the last part of the url.
         */
        std::string pruneEnd();

    private:
        void assign(const Uri &url);

        void assign(Uri &&url);

        void str_url() const;

        void lazy_parse() const { if (!m_parse) parse_url(); }

        void parse_url() const;

        mutable std::string m_scheme;
        mutable std::string m_user;
        mutable std::string m_host;
        mutable std::string m_port;
        mutable std::string m_path;
        mutable Query m_query;
        mutable std::string m_fragment;
        mutable std::string m_url;
        mutable bool m_parse{};
        mutable bool m_built{};
        mutable std::int8_t m_ip_v;
    };
}



#endif // URL_HPP

