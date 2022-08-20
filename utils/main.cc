#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <sys/queue.h>

#include <rte_memory.h>
#include <rte_launch.h>
#include <rte_eal.h>
#include <rte_per_lcore.h>
#include <rte_lcore.h>
#include <rte_debug.h>
#include <rte_ip_frag.h>

// Before compiling the program, do this command to set hugepage information:
// sudo echo 2048 > /sys/kernel/mm/hugepages/hugepages-2048kB/nr_hugepages
// source: https://mails.dpdk.org/archives/users/2021-May/005632.html

// For executing the program: sudo ./main_dp_test -l 4-7 n `0
// First parameter sets the cpu cores that we want to send "Hello World!" meassages from.
// Second parameter sets the memory channels which cpu and ram have data movement through.
// More explanation for memory channel:
// DPDK memory channels Memory channels are wire traces between the memory unit and CPU 
// for data movement. The number of memory channels acts as paths for data transfer at faster 
// rates. For OVS-DPDK, the parameter OVSDpdkMemoryChannels holds the number of actively used channels.

static int
lcore_hello(__rte_unused void *arg)
{
    
	unsigned lcore_id;
	lcore_id = rte_lcore_id();
	printf("hello from core %u\n", lcore_id);
	return 0;
}

int
main(int argc, char **argv)
{
    
	int ret;
	unsigned lcore_id;
	ret = rte_eal_init(argc, argv);
	if (ret < 0)
		rte_panic("Cannot init EAL\n");

	/* call lcore_hello() on every worker lcore */
	RTE_LCORE_FOREACH_WORKER(lcore_id) {
    
		rte_eal_remote_launch(lcore_hello, NULL, lcore_id);

	}

	/* call it on main lcore too */
	lcore_hello(NULL);


	rte_eal_mp_wait_lcore();

	/* clean up the EAL */
	rte_eal_cleanup();

	return 0;
}