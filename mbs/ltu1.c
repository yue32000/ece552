#include <stdio.h>
/*
sim_num_RAW_hazard_q1       1000933 # total number of RAW hazards (q1)
sim_num_RAW_hazard_q1_2cycles      1000854 # total number of 2-cycles RAW hazards (q1)
sim_num_RAW_hazard_q1_1cycle           79 # total number of 1-cycle RAW hazards (q1)
sim_num_RAW_hazard_q2       1000861 # total number of RAW hazards (q2)
sim_num_RAW_hazard_q2_2cycles      1000091 # total number of 2-cycles RAW hazards (q2)
sim_num_RAW_hazard_q2_1cycle          770 # total number of 1-cycle RAW hazards (q2)
CPI_from_RAW_hazard_q1       1.4997 # CPI from RAW hazard (q1)
CPI_from_RAW_hazard_q2       1.4994 # CPI from RAW hazard (q2)
*/

int  main (int argc, char *argv[])
{
    // load to use one cycle dependance distance
    __asm__(
            "li     $2, -1000000\n"
            "$loop: "
            "add    $2, $2, 1\n"        // 
            "xor    $4, $3, $3\n"       // dummy
            "lw     $5, 0($fp)\n"       // r5 <-
            "bne    $2, $5, $loop\n"    //    <- r5
    );

    return 0;
}
