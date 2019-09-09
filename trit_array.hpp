
#ifndef TRIT_ARRAY_HPP_INCLUDED
#define TRIT_ARRAY_HPP_INCLUDED

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
        inline int get(const int &ind) {
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
        unsigned char *datah;
        unsigned char *datal;
        int data_size;
        public:

        trit_array() {
            datah = NULL;
            datal = NULL;
            data_size = 0;
        };

        trit_array(const int size) {
            data_size = size/4;
            datah = new unsigned char[data_size];
            std::fill(datah, datah + data_size, '\0');
            datal = datah + data_size/2;
        };

        ~trit_array() {
            if(datah != NULL) delete [] datah;
            datah = NULL;
            datal = NULL;
        }

        /** \brief Resize Array
         * \param size new array size
         */
        inline void resize(const int size) {
            int new_size = size/4;
            unsigned char *new_arr = new unsigned char[new_size];
            int copy_size = new_size > data_size ? data_size : new_size;
            for(int i = 0; i < copy_size; ++i) {
                new_arr[i] = datah[i];
            }
            data_size = new_size;
            if(datah != NULL) delete [] datah;
            datah = new_arr;
            datal = datah + data_size/2;
        }

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
        inline int get(const int &ind) {
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
            return data_size;
        }

        trit_array & operator=(const trit_array & array) {
            if(this != &array) {
                delete [] datah;
                data_size = array.data_size;
                datah = new unsigned char[data_size];
                std::fill(datah, datah + data_size, '\0');
                std::copy(array.datah,  array.datah + data_size, datah);
                datal = datah + data_size/2;
            }
            return *this;
        }
    };

    class trit_array_2d {
        private:
        unsigned char *trit_data;
        int size_x;
        int size_y;
        int size_x_div2;
        int trit_data_size;

        inline void init(const int &size_x, const int &size_y) {
            trit_array_2d::size_x = size_x / 4;
            size_x_div2 = size_x / 8;
            trit_array_2d::size_y = size_y;
            trit_data_size = trit_array_2d::size_x * trit_array_2d::size_y;
            trit_data = new unsigned char[trit_data_size];
            std::fill(trit_data, trit_data + trit_data_size, '\0');
        }
        public:

        trit_array_2d() {
            trit_data = NULL;
            size_x = 0;
            size_y = 0;
            size_x_div2 = 0;
            trit_data_size = 0;
        }

        /** \brief Initialize a two-dimensional array
         * \param size_x row size
         * \param size_y column size
         */
        trit_array_2d(const int &size_x, const int &size_y) {
            init(size_x, size_y);
        }

        /** \brief Initialize a two-dimensional array
         * \param size_x row size
         * \param size_y column size
         * \param user_data pointer to an array with data
         */
        trit_array_2d(const int &size_x, const int &size_y, const unsigned char *user_data) {
            init(size_x, size_y);
            std::copy(user_data, user_data + trit_data_size, trit_data);
        }

        ~trit_array_2d() {
            if(trit_data != NULL) delete [] trit_data;
        }

        /** \brief Set the value of the trit
         * \param x position of an element in a row of a two-dimensional array
         * \param y position of an element in a column of a two-dimensional array
         * \param state array element state
         */
        inline void set(const int &x, const int &y, const int &state) {
            int offset_y = y*size_x;
            unsigned char *datah = trit_data + offset_y;
            unsigned char *datal = trit_data + offset_y + size_x_div2;
            int byte = x / 8;
            int offset = x % 8;
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
         * \param x position of an element in a row of a two-dimensional array
         * \param y position of an element in a column of a two-dimensional array
         * \return array element state
         */
        inline int get(const int &x, const int &y) {
            int offset_y = y * size_x;
            unsigned char *datah = trit_data + offset_y;
            unsigned char *datal = trit_data + offset_y + size_x_div2;
            int byte = x / 8;
            int offset = x % 8;
            unsigned char bit = 0x80 >> offset;
            return (datah[byte] & bit) ? BASE3_TRUE : (datal[byte] & bit) ? BASE3_FALSE : BASE3_NULL;
        }

        /** \brief Get column size
         * \return column size
         */
        inline int column_size() const {
            return size_y;
        }

        /** \brief Get row size
         * \return row size
         */
        inline int row_size() const {
            return size_x;
        }

        /** \brief Get size
         * \return size
         */
        inline int size() const {
            return trit_data_size;
        }

        /** \brief Get a pointer to a data array
         * \return array pointer
         */
        inline unsigned char *data() const {
            return trit_data;
        }

        trit_array_2d & operator=(const trit_array_2d & array_2d) {
            if(this != &array_2d) {
                delete [] trit_data;
                size_x = array_2d.size_x;
                size_y = array_2d.size_y;
                size_x_div2 = array_2d.size_x_div2;
                trit_data_size = array_2d.trit_data_size;
                trit_data = new unsigned char[trit_data_size];
                std::copy(array_2d.trit_data, array_2d.trit_data + trit_data_size, trit_data);
            }
            return *this;
        }
    };
};

#endif // TRILEAN_ARRAY_HPP_INCLUDED
