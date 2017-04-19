## pwn_lab

Short notes : 

### Heap Exploit

My code / Refrence :


<a href="https://github.com/sivaramaaa/CTF_repo/blob/master/33c3ctf/exploit.py">33c3 ctf :Heap overflow</a>
<a href="https://github.com/sivaramaaa/CTF_repo/blob/master/33c3ctf/exploit.py">plaidctf 2016: Basic UAF </a> 

### Format srting Exploit :
1) Leak all string in stack using direct parameter access 
2) Leak Whole binary by using <b>Dynelf</b> which uses the concept that 32/64 bit binary has unique entry point 
   after leaking whole text segment get libc. got addr thn got overwrite to get RCE

My code / Refrence :


<a href="https://github.com/sivaramaaa/My_tools/blob/master/Format_String">TOol to automate</a>
<a href="https://github.com/sivaramaaa/CTF_repo/blob/master/Sharifctf/Brute.py">Sharif ctf : Leak stack</a>


### Stack based exploit :

##### 64 bit rop

All parameters must be in registers and not on stack 

My code / Refrence :
<a href="https://github.com/sivaramaaa/CTF_repo/tree/master/asisctf-2017">Asis ctf </a>



