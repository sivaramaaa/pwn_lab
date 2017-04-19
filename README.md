## pwn_lab

Short notes : 

### Heap Exploit

My code / Refrence :


<a href="https://github.com/sivaramaaa/CTF_repo/blob/master/33c3ctf/exploit.py">33c3ctf : Heap overflow</a><br>
<a href="https://github.com/sivaramaaa/CTF_repo/blob/master/33c3ctf/exploit.py">plaidctf 2016: Basic UAF </a> <br>

### Format srting Exploit :
1) Leak all string in stack using direct parameter access 
2) Leak Whole binary by using <b>Dynelf</b> which uses the concept that 32/64 bit binary has unique entry point 
   after leaking whole text segment get libc. got addr thn got overwrite to get RCE

My code / Refrence :


<a href="https://github.com/sivaramaaa/My_tools/blob/master/Format_String">Tool to automate</a> <br>
<a href="https://github.com/sivaramaaa/CTF_repo/blob/master/Sharifctf/Brute.py">Sharifctf : Leak stack</a><br>


### Stack based exploit :

##### 64 bit rop

All parameters must be in registers and not on stack 

My code / Refrence :

<a href="https://github.com/sivaramaaa/CTF_repo/tree/master/asisctf-2017">Asis ctf </a>

##### Null-byte overflow
<a href="https://hackerbuck.github.io/blog/ctfx.html">ctf(x)</a>

##### Jump to shellcode

<a href="https://hackerbuck.github.io/blog/csaaw2k12_exp500.html"></a>

##### Bypass Shellcode filters 

<a href="https://hackerbuck.github.io/blog/csaw2k12_exp400.html"></a>

##### Bind tcp shellcode

<a href="https://hackerbuck.github.io/blog/csaw2k13_exp200.html"></a>

##### Pipe exploit 

<a href="https://hackerbuck.github.io/blog/secure_file_reader.html"></a>

