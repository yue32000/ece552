#include <stdio.h>
/*
sim_num_RAW_hazard_q1       1000933 # total number of RAW hazards (q1)
sim_num_RAW_hazard_q1_2cycles      1000854 # total number of 2-cycles RAW hazards (q1)
sim_num_RAW_hazard_q1_1cycle           79 # total number of 1-cycle RAW hazards (q1)
sim_num_RAW_hazard_q2       1000861 # total number of RAW hazards (q2)
sim_num_RAW_hazard_q2_2cycles      1000091 # total number of 2-cycles RAW hazards (q2)
sim_num_RAW_hazard_q2_1cycle          770 # total number of 1-cycle RAW hazards (q2)
CPI_from_RAW_hazard_q1       1.3999 # CPI from RAW hazard (q1)
CPI_from_RAW_hazard_q2       1.3997 # CPI from RAW hazard (q2)
*/

int  main (int argc, char *argv[])
{
    // load to use one and two cycle dependance distances
    __asm__(
            "li     $2, -1000000\n"
            "$loop: "
            "add    $2, $2, 1\n"        // 
            "lw     $4, 0($fp)\n"       // r4 <- mem
            "xor    $8, $4, $5\n"       // <- r4
            "xor    $6, $4, $7\n"       // <- r4
            "bne    $2, $0, $loop\n"    //  
    );

    return 0;
}
