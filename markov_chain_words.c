#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum {
    Vowel,
    Consonant
} State;

typedef struct {
    State state;
    float probability;
} Transition;

typedef struct {
    State current_state;
    Transition transitions[2];
} Node;

typedef struct {
    State current_state;
    Node nodes[2];
} MarkovChain;

const int NUM_VOWELS = 5;
const int NUM_CONSONANTS = 21;
char vowels[NUM_VOWELS] = {'a', 'e', 'i', 'o', 'u'};
char consonants[NUM_CONSONANTS] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'};

Node vowel_state = {
    .current_state = Vowel,
    .transitions = {
        {.state = Vowel, .probability = 0.1},
        {.state = Consonant, .probability = 0.9}
    }
};

Node consonant_state = {
    .current_state = Consonant,
    .transitions = {
        {.state = Vowel, .probability = 0.4},
        {.state = Consonant, .probability = 0.6}
    }
};

void do_transition(MarkovChain* mc, Node node, float p) {
    if(p <= node.transitions[0].probability) {
        mc->current_state = node.transitions[0].state;
    } else {
        mc->current_state = node.transitions[1].state;
    }
}

int main() {
    srand(time(NULL));

    MarkovChain mc = {
        .current_state = Vowel,
        .nodes = {}
    };

    mc.nodes[Vowel] = vowel_state;
    mc.nodes[Consonant] = consonant_state;

    for(int i = 0; i < 10; i++) {
        int idx;
        char letter;
        float p = (float)rand() / (float)RAND_MAX;
        Node node;

        if(mc.current_state == Vowel) {
            idx = rand() % NUM_VOWELS;
            letter = vowels[idx];

            node = mc.nodes[Vowel];
            do_transition(&mc, node, p);
        } else if(mc.current_state == Consonant) {
            idx = rand() % NUM_CONSONANTS;
            letter = consonants[idx];

            node = mc.nodes[Consonant];
            do_transition(&mc, node, p);
        } else {
            printf("Error. Uknown state.");
        }
        printf("%c", letter);
    }
    printf("\n");

    return 0;
}
