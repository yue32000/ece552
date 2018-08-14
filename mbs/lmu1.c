#include <stdio.h>
/*
sim_num_RAW_hazard_q1       2000933 # total number of RAW hazards (q1)
sim_num_RAW_hazard_q1_2cycles      2000854 # total number of 2-cycles RAW hazards (q1)
sim_num_RAW_hazard_q1_1cycle           79 # total number of 1-cycle RAW hazards (q1)
sim_num_RAW_hazard_q2       2000861 # total number of RAW hazards (q2)
sim_num_RAW_hazard_q2_2cycles      1000091 # total number of 2-cycles RAW hazards (q2)
sim_num_RAW_hazard_q2_1cycle      1000770 # total number of 1-cycle RAW hazards (q2)
CPI_from_RAW_hazard_q1       1.7993 # CPI from RAW hazard (q1)
CPI_from_RAW_hazard_q2       1.5994 # CPI from RAW hazard (q2)
*/

int  main (int argc, char *argv[])
{
    // load, modify, use. one cycle depedance distance between each
    __asm__(
            "li     $2, -1000000\n"
            "$loop: "
            "add    $2, $2, 1\n"        // 
            "lw     $5, 0($fp)\n"       // r5  <- mem
            "add    $5, $5, 1\n"        // r5  <- alu(r5)
            "add    $6, $5, 1\n"        // alu <- r5
            "bne    $2, $0, $loop\n"    //    
    );

    return 0;
}
