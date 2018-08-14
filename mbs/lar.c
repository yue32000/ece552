#include <stdio.h>
/*
sim_num_RAW_hazard_q1           929 # total number of RAW hazards (q1)
sim_num_RAW_hazard_q1_2cycles          846 # total number of 2-cycles RAW hazards (q1)
sim_num_RAW_hazard_q1_1cycle           83 # total number of 1-cycle RAW hazards (q1)
sim_num_RAW_hazard_q2           856 # total number of RAW hazards (q2)
sim_num_RAW_hazard_q2_2cycles           91 # total number of 2-cycles RAW hazards (q2)
sim_num_RAW_hazard_q2_1cycle          765 # total number of 1-cycle RAW hazards (q2)
CPI_from_RAW_hazard_q1       1.0004 # CPI from RAW hazard (q1)
CPI_from_RAW_hazard_q2       1.0002 # CPI from RAW hazard (q2)
*/

int  main (int argc, char *argv[])
{
    // loading into address register
    // WAR dependance, shouldn't be counted
    __asm__(
            "li     $2, -1000000\n"
            "add    $4, $0, $fp\n"
            "$loop: "
            "add    $2, $2, 1\n"        
            "xor    $5, $3, $3\n"        
            "lw     $4, 0($4)\n"     // <- r4, r4 <-  
            "bne    $2, $0, $loop\n"
    );

    return 0;
}
