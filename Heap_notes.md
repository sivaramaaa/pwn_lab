### Unlink Explot

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

hence if size is 0 then it points itself hence it's inuse_bit is 0 hence free() belives ti as free !!!!!!!!!!!



####  4) Patch 

     __builtin_expect (FD->bk != P || BK->fd != P, 0)


### House of mind 


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
         
          



