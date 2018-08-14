#include <stdio.h>
/*
sim_num_RAW_hazard_q1       1000934 # total number of RAW hazards (q1)
sim_num_RAW_hazard_q1_2cycles          854 # total number of 2-cycles RAW hazards (q1)
sim_num_RAW_hazard_q1_1cycle      1000080 # total number of 1-cycle RAW hazards (q1)
sim_num_RAW_hazard_q2           862 # total number of RAW hazards (q2)
sim_num_RAW_hazard_q2_2cycles           91 # total number of 2-cycles RAW hazards (q2)
sim_num_RAW_hazard_q2_1cycle          771 # total number of 1-cycle RAW hazards (q2)
CPI_from_RAW_hazard_q1       1.1668 # CPI from RAW hazard (q1)
CPI_from_RAW_hazard_q2       1.0002 # CPI from RAW hazard (q2)
*/

int  main (int argc, char *argv[])
{
    // overlapping comp to uses with two cycle dependance distance
    // second ctu should not stall
    __asm__(
            "li     $2, -1000000\n"
            "$loop: "
            "add    $2, $2, 1\n"        // 
            "xor    $5, $10, $11\n"     // r5 <-
            "xor    $4, $3, $9\n"       // r4 <-
            "xor    $8, $12, $5\n"      // <- r5
            "xor    $6, $7, $4\n"       // <- r4
            "bne    $2, $0, $loop\n"    //  
    );

    return 0;
}
