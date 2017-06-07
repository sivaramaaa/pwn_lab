## pwn_lab

Short notes : 

### Heap Exploit

#### Unlink vuln 

[Defcon Ctf - beatmeonthedl](https://github.com/sivaramaaa/CTF_repo/blob/master/DefconCTF_2017/beatmeonthedl.py)

#### UAF vuln

<a href="https://github.com/sivaramaaa/CTF_repo/blob/master/babyuaf.py">BCTF: Babyuse</a><br>
<a href="https://github.com/sivaramaaa/CTF_repo/blob/master/plaidctf_2016/unix_time_formater.py">plaidctf 2016: Basic UAF </a> <br>

#### Heap overflow 

<a href="https://github.com/sivaramaaa/CTF_repo/blob/master/33c3ctf/exploit.py">33c3ctf : Heap overflow</a><br>


### Format srting Exploit :
1) Leak all string in stack using direct parameter access 
2) Leak Whole binary by using <b>Dynelf</b> which uses the concept that 32/64 bit binary has unique entry point 
   after leaking whole text segment get libc. got addr thn got overwrite to get RCE

My code / Refrence :


<a href="https://github.com/sivaramaaa/My_tools/blob/master/Format_String">Tool to automate</a> <br>
<a href="https://github.com/sivaramaaa/CTF_repo/blob/master/Sharifctf/Brute.py">Sharifctf : Leak stack</a><br>


### Stack based exploit :

##### One-Shot-RCE gadget

If u don't have control over arguments to system() then we can use this gadget 
U can fid this gadget using the tool one_gadget . 
Usage : one_gadget -f libc.so 

[Oneshot TJCTF](https://github.com/sivaramaaa/CTF_repo/blob/master/tjctf_oneshot.py)

<a href="https://github.com/sivaramaaa/CTF_repo/blob/master/babyuaf.py">BCTF: Babyuse</a> <br>

#### Return-oriented programming (ROP)


##### 64 bit rop

All parameters must be in registers and not on stack 

[Asis ctf 64-bit rop](https://github.com/sivaramaaa/CTF_repo/tree/master/asisctf-2017)

##### Return to shellcode

Load and execute !!! 

[Defcon ctf - smashme](https://github.com/sivaramaaa/CTF_repo/blob/master/DefconCTF_2017/smashme.py)

[Ret2Shellcode](https://hackerbuck.github.io/blog/csaaw2k12_exp500.html)

###### Other stack based exploit 

[Stage'ed Shellcode](https://github.com/sivaramaaa/CTF_repo/blob/master/FireEye/stage_shellcode.py)

[Random explit](https://github.com/sivaramaaa/CTF_repo/blob/master/random_exploits.md)

[ctf(x)  Null-byte overflow  ](https://hackerbuck.github.io/blog/ctfx.html)


[Bypass Shellcode filters](https://hackerbuck.github.io/blog/csaw2k12_exp400.html)

[Bind tcp shell](https://hackerbuck.github.io/blog/csaw2k13_exp200.html)

[Pipe Exploit ](https://hackerbuck.github.io/blog/secure_file_reader.html)

