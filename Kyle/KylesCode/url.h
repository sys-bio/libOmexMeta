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

#include <vector>
#include <utility>
#include <stdexcept>
#include <cstdint>
#include <ostream>
#include <utility>

namespace semsim {
    class Url {
    public:
        // Exception thut may be thrown when decoding an URL or an assigning value
        class parse_error : public std::invalid_argument {
        public:
            parse_error(std::string &reason) : std::invalid_argument(reason) {}
        };

        // Exception that may be thrown when building an URL
        class build_error : public std::runtime_error {
        public:
            build_error(std::string &reason) : std::runtime_error(reason) {}
        };

        bool operator==(Url &rhs);

        bool operator!=(Url &rhs);

        // Default constructor
        Url() : m_parse(true), m_built(true), m_ip_v(-1) {}

        // Copy initializer constructor
        Url(Url &url) : m_ip_v(-1) { assign(url); }

        // Move constructor
        Url(Url &&url) : m_ip_v(-1) { assign(std::move(url)); }

        // Construct Url with the given string
        Url(std::string &url_str) : m_url(url_str), m_parse(false), m_built(false), m_ip_v(-1) {}

        // Assign the given URL string
        Url &operator=(std::string &url_str) { return str(url_str); }

        // Assign the given Url object
        Url &operator=(Url &url) {
            assign(url);
            return *this;
        }

        // Move the given Url object
        Url &operator=(Url &&url) {
            assign(std::move(url));
            return *this;
        }

        // Clear the Url object
        Url &clear();

        // Build Url if needed and return it as string
        std::string str() {
            if (!m_built) build_url();
            return m_url;
        }

        // Set the Url to the given string. All fields are overwritten
        Url &str(std::string &url_str) {
            m_url = url_str;
            m_built = m_parse = false;
            return *this;
        }

        // Get scheme
        std::string &scheme() {
            lazy_parse();
            return m_scheme;
        }

        // Set scheme
        Url &scheme(std::string &s);

        // Get user info
        std::string &user_info() {
            lazy_parse();
            return m_user;
        }

        // Set user info
        Url &user_info(std::string &s);

        // Get host
        std::string &host() {
            lazy_parse();
            return m_host;
        }

        // Set host
        Url &host(std::string &h, uint8_t ip_v = 0);

        // Get host IP version: 0=name, 4=IPv4, 6=IPv6, -1=undefined
        std::int8_t ip_version() {
            lazy_parse();
            return m_ip_v;
        }

        // Get port
        std::string &port() {
            lazy_parse();
            return m_port;
        }

        // Set Port given as string
        Url &port(std::string &str);

        // Set port given as a 16bit unsigned integer
        Url &port(std::uint16_t num) { return port(std::to_string(num)); }

        // Get path
        std::string &path() {
            lazy_parse();
            return m_path;
        }

        // Set path
        Url &path(std::string &str);

        class KeyVal {
        public:
            // Default constructor
            KeyVal() {}

            // Construct with provided Key and Value strings
            KeyVal(std::string &key, std::string &val) : m_key(key), m_val(val) {}

            // Construct with provided Key string, val will be empty
            KeyVal(std::string &key) : m_key(key) {}

            // Equality test operator
            bool operator==(KeyVal &q) { return m_key == q.m_key && m_val == q.m_val; }

            // Swap this with q
            void swap(KeyVal &q) {
                std::swap(m_key, q.m_key);
                std::swap(m_val, q.m_val);
            }

            // Get key
            std::string &key() { return m_key; }

            // Set key
            void key(std::string &k) { m_key = k; }

            // Get value
            std::string &val() { return m_val; }

            // Set value
            void val(std::string &v) { m_val = v; }

            // Output key value pair
            friend std::ostream &operator<<(std::ostream &o, KeyVal &kv) {
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
        Query &query() {
            lazy_parse();
            return m_query;
        }

        // Get a reference to a specific Key Value pair in the query vector for read only access
        KeyVal &query(size_t i) {
            lazy_parse();
            if (i >= m_query.size())
                throw std::out_of_range("Invalid Url query index (" + std::to_string(i) + ")");
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
                throw std::out_of_range("Invalid Url query index (" + std::to_string(i) + ")");
            m_built = false;
            return m_query[i];
        }

        // Set the query vector to the Query vector q
        Url &set_query(Query &q) {
            lazy_parse();
            if (q != m_query) {
                m_query = q;
                m_built = false;
            }
            return *this;
        }

        // Append KeyVal kv to the query
        Url &add_query(KeyVal &kv) {
            lazy_parse();
            m_built = false;
            m_query.push_back(kv);
            return *this;
        }

        // Append key val pair to the query
        Url &add_query(std::string &key, std::string &val) {
            lazy_parse();
            m_built = false;
            m_query.emplace_back(key, val);
            return *this;
        }

        // Append key with empty val to the query
        Url &add_query(std::string &key) {
            lazy_parse();
            m_built = false;
            m_query.emplace_back(key);
            return *this;
        }

        // Get the fragment
        std::string &fragment() {
            lazy_parse();
            return m_fragment;
        }

        // Set the fragment
        Url &fragment(std::string &f);

        // Output
        std::ostream &output(std::ostream &o);

        // Output strean operator
        friend std::ostream &operator<<(std::ostream &o, Url &u) { return u.output(o); }

    private:
        void assign(Url &url);

        void assign(Url &&url);

        void build_url();

        void lazy_parse() { if (!m_parse) parse_url(); }

        void parse_url();

        mutable std::string m_scheme;
        mutable std::string m_user;
        mutable std::string m_host;
        mutable std::string m_port;
        mutable std::string m_path;
        mutable Query m_query;
        mutable std::string m_fragment;
        mutable std::string m_url;
        mutable bool m_parse;
        mutable bool m_built;
        mutable std::int8_t m_ip_v;
    };
}


#endif // URL_HPP

