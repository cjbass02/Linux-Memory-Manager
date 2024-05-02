CC=gcc
CFLAGS=-Wall -g
LDFLAGS=-lpthread # Ensure correct linking with pthread library

all: testmemmgr.out pthread_testmemmgr.out test_out_of_memory_ff.out test_out_of_memory_bf.out test_out_of_memory_wf.out test_free_empty.out test_free_destroy.out test_large_heap.out test_small_heap.out test_mt_ofm_ff.out

test_mt_ofm_ff.out : memory_manager.c test_mt_ofm_ff.c linked_list.c
	$(CC) $(CFLAGS) memory_manager.c test_mt_ofm_ff.c linked_list.c -o test_mt_ofm_ff.out $(LDFLAGS)

test_small_heap.out : memory_manager.c test_small_heap.c linked_list.c
	$(CC) $(CFLAGS) memory_manager.c test_small_heap.c linked_list.c -o test_small_heap.out $(LDFLAGS)

test_large_heap.out : memory_manager.c test_large_heap.c linked_list.c
	$(CC) $(CFLAGS) memory_manager.c test_large_heap.c linked_list.c -o test_large_heap.out $(LDFLAGS)

test_free_destroy.out : memory_manager.c test_free_destroy.c linked_list.c
	$(CC) $(CFLAGS) memory_manager.c test_free_destroy.c linked_list.c -o test_free_destroy.out $(LDFLAGS)

test_free_empty.out : memory_manager.c test_free_empty.c linked_list.c
	$(CC) $(CFLAGS) memory_manager.c test_free_empty.c linked_list.c -o test_free_empty.out $(LDFLAGS)

test_out_of_memory_wf.out : memory_manager.c test_out_of_memory_wf.c linked_list.c
	$(CC) $(CFLAGS) memory_manager.c test_out_of_memory_wf.c linked_list.c -o test_out_of_memory_wf.out $(LDFLAGS)

test_out_of_memory_bf.out : memory_manager.c test_out_of_memory_bf.c linked_list.c
	$(CC) $(CFLAGS) memory_manager.c test_out_of_memory_bf.c linked_list.c -o test_out_of_memory_bf.out $(LDFLAGS)

test_out_of_memory_ff.out : memory_manager.c test_out_of_memory_ff.c linked_list.c
	$(CC) $(CFLAGS) memory_manager.c test_out_of_memory_ff.c linked_list.c -o test_out_of_memory_ff.out $(LDFLAGS)

test_few_threads.out : memory_manager.c test_few_threads.c linked_list.c
	$(CC) $(CFLAGS) memory_manager.c test_few_threads.c linked_list.c -o test_few_threads.out $(LDFLAGS)

test_many_threads.out : memory_manager.c test_many_threads.c linked_list.c
	$(CC) $(CFLAGS) memory_manager.c test_many_threads.c linked_list.c -o test_many_threads.out $(LDFLAGS)

test_allocated_space.out : memory_manager.c test_allocated_space.c linked_list.c
	$(CC) $(CFLAGS) memory_manager.c test_allocated_space.c linked_list.c -o test_allocated_space.out $(LDFLAGS)

test_remaining_space.out : memory_manager.c test_remaining_space.c linked_list.c
	$(CC) $(CFLAGS) memory_manager.c test_remaining_space.c linked_list.c -o test_remaining_space.out $(LDFLAGS)

test_malloc_count.out : memory_manager.c test_malloc_count.c linked_list.c
	$(CC) $(CFLAGS) memory_manager.c test_malloc_count.c linked_list.c -o test_malloc_count.out $(LDFLAGS)

test_fragment_count.out : memory_manager.c test_fragment_count.c linked_list.c
	$(CC) $(CFLAGS) memory_manager.c test_fragment_count.c linked_list.c -o test_fragment_count.out $(LDFLAGS)

testmemmgr.out: memory_manager.c testmemmgr.c linked_list.c
	$(CC) $(CFLAGS) memory_manager.c testmemmgr.c linked_list.c -o testmemmgr.out $(LDFLAGS)

pthread_testmemmgr.out: memory_manager.c pthread_testmemmgr.c linked_list.c
	$(CC) $(CFLAGS) memory_manager.c pthread_testmemmgr.c linked_list.c -o pthread_testmemmgr.out $(LDFLAGS)

clean:
	rm -f *.out *.gch
