#include <stdio.h>
#include<stdlib.h>
#include<math.h>


int main() {
   int p, q;
   int v[20] = {0};  // Ensure array is initialized to zero

   printf("Enter the prime number (p): ");
   scanf("%d", &p);

   printf("Enter the positive integer (q): ");
   scanf("%d", &q);

   int is_primitive_root = 1;  // Flag to check if q is a primitive root

   for (int i = 1; i < p; i++) {
       v[i] = (int)pow(q, i) % p;
       printf("%d^%d mod %d = %d\n", q, i, p, v[i]);

       // Check if the value repeats
       for (int j = 1; j < i; j++) {
           if (v[i] == v[j]) {
               is_primitive_root = 0;
               break;
           }
       }

       if (!is_primitive_root) {
           break;
       }
   }

   if (is_primitive_root) {
       printf("%d is a primitive root of %d.\n", q, p);
   } else {
       printf("%d is not a primitive root of %d.\n", q, p);
   }

   return 0;
}