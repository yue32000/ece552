#include <stdio.h>
/*
sim_num_RAW_hazard_q1       2000936 # total number of RAW hazards (q1)
sim_num_RAW_hazard_q1_2cycles      2000854 # total number of 2-cycles RAW hazards (q1)
sim_num_RAW_hazard_q1_1cycle           82 # total number of 1-cycle RAW hazards (q1)
sim_num_RAW_hazard_q2       1000864 # total number of RAW hazards (q2)
sim_num_RAW_hazard_q2_2cycles           91 # total number of 2-cycles RAW hazards (q2)
sim_num_RAW_hazard_q2_1cycle      1000773 # total number of 1-cycle RAW hazards (q2)
CPI_from_RAW_hazard_q1       1.7993 # CPI from RAW hazard (q1)
CPI_from_RAW_hazard_q2       1.1999 # CPI from RAW hazard (q2)
*/

int  main (int argc, char *argv[])
{
    // comp to use and chained comp to store, both one cycle dependance distance
    __asm__(
            "li     $2, -1000000\n"
            "$loop: "
            "add    $2, $2, 1\n"        
            "addi   $3, $0, 1\n"        // r3 <- alu
            "xor    $4, $3, $3\n"       // r4 <- alu(r3)
            "sw     $4, 0($fp)\n"       // mem <- r4
            "bne    $2, $0, $loop\n"    
    );

    return 0;
}
