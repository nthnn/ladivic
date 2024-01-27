#include <iostream>
#include <ldvc_mem.hpp>
#include <ldvc_type.hpp>

using namespace std;

i32 main() {
    i32* i32_array = ldvc_malloc<i32>(5);
    for(usize i = 0; i < 5; ++i)
        i32_array[i] = static_cast<i32>(i * 10);

    cout << "Original Array: ";
    for(usize i = 0; i < 5; ++i)
        std::cout << i32_array[i] << " ";
    cout << endl;

    i32* resized_array = ldvc_realloc(i32_array, 10);
    for(usize i = 5; i < 10; ++i)
        resized_array[i] = static_cast<i32>(i * 10);

    cout << "Resized Array: ";
    for(usize i = 0; i < 10; ++i)
        cout << resized_array[i] << " ";
    cout << endl;

    ldvc_free(resized_array);

    i32* zero_init_array = ldvc_calloc<i32>(8);
    cout << "Zero-Initialized Array: ";

    for(usize i = 0; i < 8; ++i)
        cout << zero_init_array[i] << " ";
    cout << endl;

    ldvc_free(zero_init_array);
    return 0;
}
