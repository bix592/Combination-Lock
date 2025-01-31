#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>


int combi(int N, int S, int E);

int main() {
    clock_t start, end;
    double runtime, total_runtime, fin_runtime;
    srand(time(NULL));
    int N, S, E, max, min;

    // //check runtime for same length
    total_runtime = 0;
     for (int i=0; i<1000; i++) {
        N = 50;
        S = rand() % ((int)pow(N,N-1) - (int)(pow(N,N) - 1) + 1) + (int)(pow(N,N) - 1);
        E = rand() % ((int)pow(N,N-1) - (int)(pow(N,N) - 1) + 1) + (int)(pow(N,N) - 1);
        start = clock();
        int hello = combi(N, S, E);
        end = clock();
        runtime = end - start;
        total_runtime += runtime;
     };
    fin_runtime = (double)(total_runtime) / CLOCKS_PER_SEC ;
    printf("Runtime for same length: %.6f \n", fin_runtime);


    //check runtime for different length
    total_runtime = 0;
     for (int i=0; i<1000; i++) {
        N = rand() % 100 + 3;
        S = rand() % ((int)pow(N,N-1) - (int)(pow(N,N) - 1) + 1) + (int)(pow(N,N) - 1);
        E = rand() % ((int)pow(N,N-1) - (int)(pow(N,N) - 1) + 1) + (int)(pow(N,N) - 1);
        start = clock();
        int hello = combi(N, S, E);
        end = clock();
        runtime = end - start;
        total_runtime += runtime;
     };
    fin_runtime = (double)(total_runtime) / CLOCKS_PER_SEC ;
    printf("Runtime for different length: %.6f \n", fin_runtime);
}

//program
int combi(int N, int S_int, int E_int) {
    int total_steps = 0, S, E, step_a, step_b, exp, Eh;
    for (int i=0; i<N; i++) {
         S = (S_int / (int)pow(10, i)) % 10;
         E = (E_int / (int)pow(10, i)) % 10;

        asm (
            "mov %[S], %%eax;"   // Move S into eax register
            "mov %[E], %%ebx;"    // Move E into ebx register
            "cmp %%ebx, %%eax;"   // cmp E, S
            "jg larger;"          // Jump to 'larger' if S > E

            //ELSE: when S =< E
                "mov %%eax, %%ecx;"     // copy S to ecx (smaller)
                "mov %%ebx, %%edx;"     //copy E to edx (larger)
                "sub %%eax, %%ebx;"     // E(ebx) - S(eax) store to E(ebx)
                "mov %%ebx, %[step_a];" // store difference to step_a
                "jmp checkB;"           // Jump to 'checkB'

            // when S > E
            "larger:"
                "mov %%ebx, %%ecx;"     // copy E to ecx (smaller)
                "mov %%eax, %%edx;"     //copy S to edx (larger)     
                "sub %%ebx, %%eax;"     // S - E store to S
                "mov %%eax, %[step_a];" // store difference to step_a
                "jmp checkB;"
           
            "checkB:"
                "add $10, %%ecx;"
                "mov %%ecx, %[step_b];"
                "sub %%edx, %[step_b];"
                "jmp AorB;"

            //determine smaller of step_a and step_b. ASSUME step_a is smaller
            "AorB:"
                "mov %[step_a], %%eax;"
                "mov %[step_b], %%ebx;"
                "cmp %%eax, %%ebx;"   // cmp step_a, step_b
                "jl smaller;"         // Jump to 'smaller' if step_b < step_a
                "jmp done;"            // else if step_a is smaller, jump to "done"

            "smaller:" //step_b < step_a
                "mov %%ebx, %[step_a];"
           
            "done:" 
            : [step_a] "=r" (step_a), [step_b] "=r" (step_b) // Output operands
            : [S] "r" (S), [E] "r" (E) // Input operands
            : "%eax", "%ebx", "%ecx", "%edx"  // Clobbered registers    
        );
    total_steps += step_a;
    } 
}

