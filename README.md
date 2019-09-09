# trit_array_cpp
C++ header-only library of a trit array

### Description and examples
* trit - ternary digit
* in balanced ternary, each digit has one of 3 values: −1, 0, or +1

```C++
#include <iostream>
#include "trit_array.hpp"

int main() {
    std::cout << "Hello world!" << std::endl;
	
	// Create a two-dimensional array of trits
	base3::trit_array_2d array_2d;
	
	// Set the size of a two-dimensional array
	const int SIZE_X = 1000;
    const int SIZE_Y = 100;
	//base3::trit_array_2d array_2d(SIZE_X, SIZE_Y); - this option is also possible
	array_2d = base3::trit_array_2d(SIZE_X,SIZE_Y);
	
	// Set the value of the trit
	array_2d.set(55, 34, base3::BASE3_TRUE); // Set +1
	array_2d.set(156, 87, base3::BASE3_FALSE); // Set -1
	array_2d.set(3, 8, base3::BASE3_NULL); // Set 0
	
	// Get the value of trit
	int state = array_2d.get(55, 34);
	if(state == base3::BASE3_TRUE) std::cout << "true" << std::endl;
	
	// size of two-dimensional array of trit
	int data_size = array_2d.size();
    std::cout << "size: " << data_size << std::endl << std::flush;
	
	// pointer to array data
	unsigned char *point_data = array_2d.data();
	
	// Initialize a new array of trites with an array of bytes
	unsigned char *array_data = new unsigned char[data_size];
    std::copy(point_data, point_data + data_size, array_data);
	base3::trit_array_2d new_array_2d(SIZE_X, SIZE_Y, array_data);
	
    return 0;
}
```

