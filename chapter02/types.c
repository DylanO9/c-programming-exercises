#include <stdio.h>

// Purpose: Determine the ranges of char, short, int, and long variables, unsigned and signed, by printing appropriate values from standard headers and by direct computation.

typedef struct {
    unsigned long long value1;
    unsigned long long value2;
} Range;

Range get_range(bool is_signed, int size_in_bytes);


int main() {
    Range r_char = get_range(false, sizeof(unsigned char));
    Range r_int = get_range(false, sizeof(unsigned int));
    Range r_short = get_range(false, sizeof(unsigned short));
    Range r_long = get_range(false, sizeof(unsigned long));
    printf("%llu-%llu\n", r_char.value1, r_char.value2);  
    printf("%llu-%llu\n", r_int.value1, r_int.value2);  
    printf("%llu-%llu\n", r_short.value1, r_short.value2);  
    printf("%llu-%llu\n", r_long.value1, r_long.value2);  
    return 0;
}

Range get_range(bool is_signed, int size_in_bytes) {
    int size_in_bits = size_in_bytes * 8;
    
    Range ans;
    ans.value1 = 0;
    unsigned long long total = 1;
    unsigned long long prev = total;
    for (int i = 0; i < size_in_bits; i++) {
        prev = total;
        total *= 2;
        if (prev > total) {
            ans.value2 = prev-1;
            return ans;    
        }
    }
    
    
    ans.value2 = total - 1; // Subtract 1 because the range is inclusive and includes 0
    return ans;
}
