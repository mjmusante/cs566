#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdint.h>

#define SMALL	10000
#define	MEDIUM	100000
#define LARGE	1000000

uint32_t array[LARGE];

#if 0
void
dump_array(uint32_t max)
{
	uint32_t i;

	for (i = 0; i < 10; i++)
		printf(" %u", array[i]);
	printf(" ...");
	for (i = max - 10; i < max; i++)
		printf(" %u", array[i]);
	printf("\n");
}
#endif

void
forward_fill(uint32_t max)
{
	uint32_t i;

	for (i = 0; i < max; i++)
		array[i] = i;
}

void
reverse_fill(uint32_t max)
{
	uint32_t i;
	
	for (i = 0; i < max; i++)
		array[i] = max - i;
}

void
random_fill(uint32_t max)
{
	uint32_t i;

	for (i = 0; i < max; i++)
		array[i] = (uint32_t) (drand48() * (double) max);
}

uint64_t
selection_sort(uint32_t max)
{
	uint32_t i;
	uint64_t count = 0;

	for (i = 0; i < max; i++) {
		uint32_t j, min = i;
		for (j = i + 1; j < max; j++) {
			++count;			// comparison
			if (array[j] < array[min])
				min = j;
		}
		if (min != i) {
			uint32_t value = array[i];
			array[i] = array[min];
			array[min] = value;
			++count;			// swap
		}
	}

	return (count);
}

uint64_t
insertion_sort(uint32_t max)
{
	uint32_t i;
	uint64_t count = 0;

	for (i = 1; i < max; i++) {
		uint32_t value = array[i];
		uint32_t j = i - 1;
		while (j < max && array[j] > value) {
			++count;			// comparison
			array[j + 1] = array[j];
			--j;
		}
		array[j + 1] = value;
		++count;				// insertion
	}

	return (count);
}

void
report_tests(uint32_t max)
{
	printf("In order, size %u\n", max);
	forward_fill(max);
	printf("\tselection sort: %llu\n", selection_sort(max));
	forward_fill(max);
	printf("\tinsertion sort: %llu\n", insertion_sort(max));

	printf("Reverse order, size %u\n", max);
	reverse_fill(max);
	printf("\tselection sort: %llu\n", selection_sort(max));
	reverse_fill(max);
	printf("\tinsertion sort: %llu\n", insertion_sort(max));

	printf("Random, size %u\n", max);
	random_fill(max);
	printf("\tselection sort: %llu\n", selection_sort(max));
	random_fill(max);
	printf("\tinsertion sort: %llu\n", insertion_sort(max));
}

int
main(int argc, char *argv)
{
	uint32_t result;

	srand48(time(0));

	report_tests(SMALL);
	report_tests(MEDIUM);
	report_tests(LARGE);
	return (0);
}
