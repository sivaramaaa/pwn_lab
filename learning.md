### My Myth breaking facts and methods to pwn :  

* Where to write  :

    * if possible overwrite eip

    * else try GOT table addrs

    * Here comes myth breaker --->  u can also overwrite <b> libc </b> location (__malloc__hook etc ..)
    
* What to write 

    * if u have leak
    
      * shellcode addr if nx is disabled 
      * Ret2libc 
          * 32 bit : &system+dummy+&binsh
          * 64 bit : &(pop rdi ; ret ; )+&binsh+&system    
          
* if no leak 

    * ROP
    * stack pivot (i.e change rsp to location where u have ropchain loaded )
    
