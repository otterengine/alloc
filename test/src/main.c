
/* A friendly warning from bake.test
 * ----------------------------------------------------------------------------
 * This file is generated. To add/remove testcases modify the 'project.json' of
 * the test project. ANY CHANGE TO THIS FILE IS LOST AFTER (RE)BUILDING!
 * ----------------------------------------------------------------------------
 */

#include <test.h>

// Testsuite 'align'
void align_forward(void);
void align_backward(void);
void align_is_aligned(void);
void align_size_forward(void);
void align_size_backward(void);

bake_test_case align_testcases[] = {
    {
        "forward",
        align_forward
    },
    {
        "backward",
        align_backward
    },
    {
        "is_aligned",
        align_is_aligned
    },
    {
        "size_forward",
        align_size_forward
    },
    {
        "size_backward",
        align_size_backward
    }
};


static bake_test_suite suites[] = {
    {
        "align",
        NULL,
        NULL,
        5,
        align_testcases
    }
};

int main(int argc, char *argv[]) {
    return bake_test_run("test", argc, argv, suites, 1);
}
