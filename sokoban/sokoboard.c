#include <ltsmin/pins.h>

// state slot values
static const int EMPTY = 0;    // " " or "."
static const int BOX = 1;      // "$"
static const int MAN = 2;      // "@"

// transition labels
static const int WALK_LEFT = 0;
static const int PUSH_LEFT = 1;
static const int WALK_RIGHT = 2;

// state labels
static const int LABEL_GOAL = 0;

int group_count() {
    return 3;
}

int state_length() {
    return 3;
}

int label_count() {
    return 1;
}

int next_state(void* model, int group, int *src, TransitionCB callback, void *arg) {

    int dst[state_length()]; // the next state values
    memcpy(dst, src, sizeof(int) * state_length()); // not all variables are modified so copy the source state

    // provide transition labels and group number of transition.
    int action[1];
    transition_info_t transition_info = { action, group };

    if (group == 0 && src[1] == EMPTY && src[2] == MAN) {
        dst[1] = MAN;
        dst[2] = EMPTY;
        action[0] = WALK_LEFT;
        int cpy[3] = {1,0,0}; // provide modified variables
        callback(arg, &transition_info, dst, cpy);
        return 1; // return number of successors
    } else if (group == 1 && src[1] == MAN && src[2] == EMPTY) {
        dst[1] = EMPTY;
        dst[2] = MAN;
        action[0] = WALK_RIGHT;
        int cpy[3] = {1,0,0}; // provide modified variables
        callback(arg, &transition_info, dst, cpy);
        return 1; // return number of successors
    } else if (group == 2 && src[0] == EMPTY && src[1] == BOX && src[2] == MAN) {
        dst[0] = BOX;
        dst[1] = MAN;
        dst[2] = EMPTY;
        action[0] = PUSH_LEFT;
        int cpy[3] = {0,0,0}; // provide modified variables
        callback(arg, &transition_info, dst, cpy);
        return 1; // return number of successors
    }
    return 0; // return number of successors
}

int initial[3];
int* initial_state() {
    initial[0] = EMPTY; initial[1] = BOX; initial[2] = MAN;
    return initial;
}

int rm[3][3] = {
    {1,1,1},
    {1,1,1},
    {1,1,1}};
int* read_matrix(int row) {
    return rm[row];
}

int wm[3][3] = {
    {1,1,1},
    {1,1,1},
    {1,1,1}};
int* write_matrix(int row) {
    return wm[row];
}

int lm[1][3] = {
    {1,0,0}
};
int* label_matrix(int row) {
    return lm[row];
}

int state_label(void* model, int label, int* src) {
    return label == LABEL_GOAL && src[0] == BOX;
}
