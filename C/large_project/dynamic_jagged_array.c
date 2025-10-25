// Dynamic Array Les go
// [p1,p2,p3,p4,p5] -> [[[p1,p2,p3]],p4,[p5]]
// int** metadata; 
// [
//     [1,0,1],
//     [3,-1,0]
// ]
// int* precompute;
// [3,1,1]
// [
//   [ 
//     [
//       [
//         p1,
//         p2,
//         [
//           p3,
//           [
//             p4,
//             p5,
//             [
//               p6
//             ]
//           ]
//         ]
//       ]
//     ]
//   ], 
//   [
//     p7
//   ], 
//   [
//     p8,
//     [
//       p9
//     ]
//   ], 
//   p10, 
//   p11
// ]


#include <stdlib.h>


typedef struct {
    int parent;      // parent node id (-1 untuk root)
    int nchild;      // jumlah anak
    int* child;      // array index anak-anak
    int* offsets;    // hasil precompute: offset prefix untuk anak-anak
} JA_Node;

typedef struct {
    void* data;      // flatten data [p1, p2, ...]
    size_t size;     // total leaf
    size_t cap;

    int dimension;   // dimensi max

    JA_Node* nodes;  // array of nodes
    size_t nnode;    // jumlah node (termasuk internal dan leaf)

    void* ext;       // extension
} jagged_array;