### My Myth breaking facts and methods to pwn :  

* Where to write  :

    * if possible overwrite eip

    * else try GOT table addrs

    * Here comes myth breaker --->  u can also overwrite <b> libc </b> location ( <b> __malloc__hook  </b> etc ..)
     
* What to write 

    * if u have leak
    
      * shellcode addr if nx is disabled
      
      * Ret2libc
      
          * 32 bit : &system+dummy+&binsh
          * 64 bit : &(pop rdi ; ret ; )+&binsh+&system   
          
      * <b> One - gadget </b>    
          
    * if no leak 

      * <b> ROP </b>
      * <b> Stack pivot </b> (i.e change rsp to location where u have ropchain loaded )
    
