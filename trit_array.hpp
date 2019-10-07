#ifndef TRIT_ARRAY_HPP_INCLUDED
#define TRIT_ARRAY_HPP_INCLUDED

#include <memory>

namespace base3 {

    /// Balanced ternary digits values
    enum {
        BASE3_TRUE = 1,
        BASE3_NULL = 0,
        BASE3_FALSE = -1,
    };

    /** \brief Static array of trit
     */
    template <int ARRAY_SIZE>
    class trit_static_array {
        private:
        unsigned char *datah[ARRAY_SIZE/4];
        unsigned char *datal;

        public:

        trit_static_array() {
            std::fill(datah, datah + ARRAY_SIZE/4, '\0');
            datal = datah + ARRAY_SIZE/8;
        };

        /** \brief Set the value of the trit
         * \param ind array element number
         * \param state array element state
         */
        inline void set(const int &ind, const int &state) {
            int byte = ind / 8;
            int offset = ind % 8;
            if(state == BASE3_NULL) {
                unsigned char mask = ~(0x80 >> offset);
                datah[byte] &= mask;
                datal[byte] &= mask;
            } else
            if(state >= BASE3_TRUE) {
                unsigned char bit = 0x80 >> offset;
                unsigned char mask = ~bit;
                datah[byte] |= bit;
                datal[byte] &= mask;
            } else {
                unsigned char bit = 0x80 >> offset;
                unsigned char mask = ~bit;
                datah[byte] &= mask;
                datal[byte] |= bit;
            }
        }

        /** \brief Get the value of the trit
         * \param ind array element number
         * \return array element state
         */
        inline int get(const int &ind) const {
            int byte = ind / 8;
            int offset = ind % 8;
            unsigned char bit = 0x80 >> offset;
            return (datah[byte] & bit) ? BASE3_TRUE : (datal[byte] & bit) ? BASE3_FALSE : BASE3_NULL;
        }

        /** \brief Get a pointer to a data array
         * \return array pointer
         */
        inline unsigned char *data() const {
            return datah;
        }

        /** \brief Get array size
         * \return array size
         */
        inline int size() const {
            return ARRAY_SIZE/8;
        }

        trit_static_array & operator=(const trit_static_array & array) {
            if(this != &array) {
                std::copy(array.datah,  array.datah + ARRAY_SIZE/4, datah);
            }
            return *this;
        }
    };

    /** \brief Array of trit
     */
    class trit_array {
        private:
        std::unique_ptr<unsigned char[]> trit_data;
        unsigned char *datah;
        unsigned char *datal;
        size_t data_size;
        public:

        trit_array() {
            datah = NULL;
            datal = NULL;
            data_size = 0;
        };

        trit_array(const size_t &size) {
            size_t new_data_size = size/4;
            if(data_size != new_data_size) {
                data_size = new_data_size;
                trit_data = std::unique_ptr<unsigned char[]>(new unsigned char[data_size]);
            }
            datah = trit_data.get();
            std::fill(datah, datah + data_size, '\0');
            datal = datah + data_size/2;
        };

        ~trit_array() {
            datah = NULL;
            datal = NULL;
        }

        /** \brief Resize Array
         * \param size new array size
         */
        inline void resize(const size_t &size) {
            size_t new_size = size/4;
            size_t copy_size = new_size > data_size ? data_size : new_size;
            std::unique_ptr<unsigned char[]> old_trit_data(new unsigned char[copy_size]);
            unsigned char *point_old_arr = old_trit_data.get();
            for(size_t i = 0; i < copy_size; ++i) {
                point_old_arr[i] = datah[i];
            }
            trit_data = std::unique_ptr<unsigned char[]>(new unsigned char[new_size]);
            datah = trit_data.get();
            std::fill(datah, datah + new_size, '\0');
            for(size_t i = 0; i < copy_size; ++i) {
                datah[i] = point_old_arr[i];
            }
            data_size = new_size;
            datal = datah + data_size/2;
        }

        /** \brief Set the value of the trit
         * \param ind array element number
         * \param state array element state
         */
        inline void set(const uint32_t &ind, const int &state) {
            uint32_t byte = ind / 8;
            uint32_t offset = ind % 8;
            if(state == BASE3_NULL) {
                unsigned char mask = ~(0x80 >> offset);
                datah[byte] &= mask;
                datal[byte] &= mask;
            } else
            if(state >= BASE3_TRUE) {
                unsigned char bit = 0x80 >> offset;
                unsigned char mask = ~bit;
                datah[byte] |= bit;
                datal[byte] &= mask;
            } else {
                unsigned char bit = 0x80 >> offset;
                unsigned char mask = ~bit;
                datah[byte] &= mask;
                datal[byte] |= bit;
            }
        }

        /** \brief Get the value of the trit
         * \param ind array element number
         * \return array element state
         */
        inline int get(const uint32_t &ind) const {
            uint32_t byte = ind / 8;
            uint32_t offset = ind % 8;
            unsigned char bit = 0x80 >> offset;
            return (datah[byte] & bit) ? BASE3_TRUE : (datal[byte] & bit) ? BASE3_FALSE : BASE3_NULL;
        }

        /** \brief Get a pointer to a data array
         * \return array pointer
         */
        inline unsigned char *data() const {
            return datah;
        }

        /** \brief Get array size
         * \return array size
         */
        inline int size() const {
            return data_size;
        }

        trit_array & operator=(const trit_array & array) {
            if(this != &array) {
                data_size = array.data_size;
                trit_data = std::unique_ptr<unsigned char[]>(new unsigned char[data_size]);
                datah = trit_data.get();
                std::fill(datah, datah + data_size, '\0');
                std::copy(array.datah,  array.datah + data_size, datah);
                datal = datah + data_size/2;
            }
            return *this;
        }
    };

    /** \brief 2d trit array
     */
    class trit_array_2d {
        private:
        std::unique_ptr<unsigned char[]> trit_data;
        size_t size_x;
        size_t size_y;
        size_t size_x_div2;
        size_t trit_data_size;

        public:

        /** \brief Initialize a two-dimensional array
         * \param user_size_x row size
         * \param user_size_y column size
         */
        inline void init(const size_t &user_size_x, const size_t &user_size_y) {
            size_y = user_size_y;
            size_x = user_size_x / 4;
            size_x_div2 = user_size_x / 8;
            size_t new_trit_data_size = size_x * size_y;
            if(trit_data_size != new_trit_data_size) {
                trit_data_size = new_trit_data_size;
                trit_data = std::unique_ptr<unsigned char[]>(new unsigned char[trit_data_size]);
            }
            unsigned char *point_trit_data = trit_data.get();
            std::fill(point_trit_data, point_trit_data + trit_data_size, '\0');
        }

        trit_array_2d() :
                size_x(0), size_y(0), size_x_div2(0), trit_data_size(0) {
        }

        /** \brief Initialize a two-dimensional array
         * \param user_size_x row size
         * \param user_size_y column size
         */
        trit_array_2d(const size_t &user_size_x, const size_t &user_size_y) :
                size_x(0), size_y(0), size_x_div2(0), trit_data_size(0) {
            init(user_size_x, user_size_y);
        }

        /** \brief Initialize a two-dimensional array
         * \param size_x row size
         * \param size_y column size
         * \param user_data pointer to an array with data
         */
        void init(const size_t &user_size_x, const size_t &user_size_y, const unsigned char *user_data) {
            init(user_size_x, user_size_y);
            unsigned char *point_trit_data = trit_data.get();
            std::copy(user_data, user_data + trit_data_size, point_trit_data);
        }

        /** \brief Initialize a two-dimensional array
         * \param size_x row size
         * \param size_y column size
         * \param user_data pointer to an array with data
         */
        trit_array_2d(const size_t &user_size_x, const size_t &user_size_y, const unsigned char *user_data) :
                size_x(0), size_y(0), size_x_div2(0), trit_data_size(0) {
            init(user_size_x, user_size_y, user_data);
        }

        ~trit_array_2d() {}

        /** \brief Set the value of the trit
         * \param x position of an element in a row of a two-dimensional array
         * \param y position of an element in a column of a two-dimensional array
         * \param state array element state
         */
        inline void set(const size_t &x, const size_t &y, const int &state) {
            size_t offset_y = y * size_x;
            size_t byte = x / 8;
            size_t offset = x % 8;
            size_t offset_h = offset_y + byte;
            size_t offset_l = offset_h + size_x_div2;
            unsigned char *point_trit_data = trit_data.get();
            if(state == BASE3_NULL) {
                unsigned char mask = ~(0x80 >> offset);
                point_trit_data[offset_h] &= mask;
                point_trit_data[offset_l] &= mask;
            } else
            if(state >= BASE3_TRUE) {
                unsigned char bit = 0x80 >> offset;
                unsigned char mask = ~bit;
                point_trit_data[offset_h] |= bit;
                point_trit_data[offset_l] &= mask;
            } else {
                unsigned char bit = 0x80 >> offset;
                unsigned char mask = ~bit;
                point_trit_data[offset_h] &= mask;
                point_trit_data[offset_l] |= bit;
            }
        }

        /** \brief Get the value of the trit
         * \param x position of an element in a row of a two-dimensional array
         * \param y position of an element in a column of a two-dimensional array
         * \return array element state
         */
        inline int get(const size_t &x, const size_t &y) const {
            size_t offset_y = y * size_x;
            size_t byte = x / 8;
            size_t offset_h = offset_y + byte;
            unsigned char offset = x % 8;
            unsigned char bit = 0x80 >> offset;
            unsigned char *point_trit_data = trit_data.get();
            return (point_trit_data[offset_h] & bit) ? BASE3_TRUE : (point_trit_data[offset_h + size_x_div2] & bit) ? BASE3_FALSE : BASE3_NULL;
        }

        /** \brief Get column size
         * \return column size
         */
        inline size_t column_size() const {
            return size_y;
        }

        /** \brief Get row size
         * \return row size
         */
        inline size_t row_size() const {
            return size_x;
        }

        /** \brief Get size
         * \return size
         */
        inline size_t size() const {
            return trit_data_size;
        }

        /** \brief Get a pointer to a data array
         * \return array pointer
         */
        inline const unsigned char *data() const {
            return (const unsigned char *)trit_data.get();
        }

        trit_array_2d & operator=(const trit_array_2d &array_2d) {
            if(this != &array_2d) {
                size_x = array_2d.size_x;
                size_y = array_2d.size_y;
                size_x_div2 = array_2d.size_x_div2;
                if(trit_data_size != array_2d.trit_data_size) {
                    trit_data_size = array_2d.trit_data_size;
                    trit_data = std::unique_ptr<unsigned char[]>(new unsigned char[trit_data_size]);
                }
                unsigned char *dst_trit_data = trit_data.get();
                unsigned char *src_trit_data = array_2d.trit_data.get();
                std::copy(src_trit_data, src_trit_data + trit_data_size, dst_trit_data);
            }
            return *this;
        }

        trit_array_2d(const trit_array_2d &array_2d) :
            size_x(0), size_y(0), size_x_div2(0), trit_data_size(0) {
            if(this != &array_2d) {
                size_x = array_2d.size_x;
                size_y = array_2d.size_y;
                size_x_div2 = array_2d.size_x_div2;
                if(trit_data_size != array_2d.trit_data_size) {
                    trit_data_size = array_2d.trit_data_size;
                    trit_data = std::unique_ptr<unsigned char[]>(new unsigned char[trit_data_size]);
                }
                unsigned char *dst_trit_data = trit_data.get();
                unsigned char *src_trit_data = array_2d.trit_data.get();
                std::copy(src_trit_data, src_trit_data + trit_data_size, dst_trit_data);
            }
        }
    };
};

#endif // TRILEAN_ARRAY_HPP_INCLUDED
