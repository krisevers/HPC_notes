#include <stddef.h>
#include <stdio.h>

#include "hh.h"

struct Parameters params = {
    .g_Na = 120.0,    
    .g_K = 36.0,      
    .g_L = 0.3,       
    .E_Na = 50.0,     
    .E_K = -77.0,    
    .E_L = -54.387,   
    .C_m = 1.0,       
    .V_rest = -65.0   
};

struct State state = {
    .V = -65.0,      
    .m = 0.05,       
    .h = 0.6,        
    .n = 0.32        
};

void callback(double t, const struct State* s, void* user) {
    // Save t and V to a file for plotting
    static FILE* fp = NULL;
    if (!fp) {
        fp = fopen("voltage_trace.dat", "w");
        if (!fp) {
            perror("Failed to open file");
            return;
        }
    }
    fprintf(fp, "%.6f %.6f\n", t, s->V);
    fflush(fp);
}

int main(int argc, char** argv) {

    // Call simulate
    simulate(&params, &state, 10.0, 100.0, 0.01, callback, NULL);

}