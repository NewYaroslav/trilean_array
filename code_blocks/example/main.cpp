#include <iostream>
#include "trit_array.hpp"

using namespace std;

int main() {
    std::cout << "Hello trit!" << std::endl;

    base3::trit_array_2d array_2d;

    const int SIZE_X = 1000;
    const int SIZE_Y = 100;

    std::cout << "init two-dimensional array" << std::endl << std::flush;
    array_2d = base3::trit_array_2d(SIZE_X,SIZE_Y);

    std::cout << "set trit" << std::endl << std::flush;
    array_2d.set(0,0,base3::BASE3_TRUE);
    array_2d.set(55,34,base3::BASE3_TRUE);
    array_2d.set(0,1,base3::BASE3_TRUE);
    array_2d.set(2,0,base3::BASE3_TRUE);
    array_2d.set(2,0,base3::BASE3_FALSE);
    array_2d.set(3,0,base3::BASE3_FALSE);
    array_2d.set(4,0,base3::BASE3_TRUE);

    std::cout << "check get trit" << std::endl << std::flush;
    for(int x = 0; x < SIZE_X; ++x) {
        for(int y = 0; y < SIZE_Y; ++y) {
            int state = array_2d.get(x, y);
            if(state == base3::BASE3_TRUE) std::cout << "x " << x << " y " << y << " true" << std::endl << std::flush;
            else if(state == base3::BASE3_FALSE) std::cout << "x " << x << " y " << y << " false" << std::endl << std::flush;
        }
    }

    std::cout << "copy data" << std::endl << std::flush;
    int data_size = array_2d.size();
    std::cout << "data size: " << data_size << std::endl << std::flush;

    unsigned char *array_data = new unsigned char[data_size];
    const unsigned char *point_2d_data = array_2d.data();
    std::copy(point_2d_data, point_2d_data + data_size, array_data);

    std::cout << "check get trit" << std::endl << std::flush;
    for(int x = 0; x < SIZE_X; ++x) {
        for(int y = 0; y < SIZE_Y; ++y) {
            int state = array_2d.get(x, y);
            if(state == base3::BASE3_TRUE) std::cout << "x " << x << " y " << y << " true" << std::endl << std::flush;
            else if(state == base3::BASE3_FALSE) std::cout << "x " << x << " y " << y << " false" << std::endl << std::flush;
        }
    }

    if(true) {
        std::cout << "init new two-dimensional array" << std::endl << std::flush;
        base3::trit_array_2d new_array_2d(SIZE_X, SIZE_Y, array_data);

        std::cout << "check get trit (new two-dimensional array)" << std::endl << std::flush;
        for(int x = 0; x < SIZE_X; ++x) {
            for(int y = 0; y < SIZE_Y; ++y) {
                int state = new_array_2d.get(x, y);
                if(state == base3::BASE3_TRUE) std::cout << "x " << x << " y " << y << " true" << std::endl << std::flush;
                else if(state == base3::BASE3_FALSE) std::cout << "x " << x << " y " << y << " false" << std::endl << std::flush;
            }
        }
        std::cout << "end check" << std::endl << std::flush;
    }

    delete [] array_data;

    std::cout << "end" << std::endl << std::flush;
    return 0;
}
