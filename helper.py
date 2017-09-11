arch = ''
nx = ''
leak = ''
def gather_info():
	global arch
	global nx
	global leak
	arch = raw_input('[-] Enter the arch: ')
        nx   = raw_input('[-] Is nx enabled (y/n) :  ')
	leak = raw_input('[-] Do u have a leak (y/n): ')


def where():

	print "[+] Try to overwrite PC ($rip)\n "
	print "[+] Try to overwrite GOT \n"
	print "[+] Try to overwrite __malloc__hook (located in libc)\n"

def what():

	if nx == 'y':
	  if leak == 'n':
	   
	    print "[+] Use Ropgadet\n"
            print "[+] Try to use pivot stack if no control over stack\n "

	  elif arch == '64' :

	    print "[+] Ret2libc and pass argument using gadget (like pop rdi ; ret).\n" 
            print "[+] If it is a 8 word write only then search for a function to pass /bin/sh."
            print "    For ex. puts(buff), free(ptr) etc ..\n"
	    print "[+] If u can't control system parameter try onegadget\n"

	  else: 
	    
	    print "[+] Ret2libc : &system+dummy+&binsh \n"
            print "[+] If it is a 4 word write only then search for a function to pass /bin/sh"
            print "    For ex. puts(buff), free(ptr) etc ..\n"
	    print "[+] If u can't control system parameter  try onegadget \n"
		
	else:
	  print "[+] Try to execte ur shellcode\n"
          print "[+] Use call eax , jmp eax to ret2shellcode\n"	
	  print "[+] Try to store ur shellcode in bss and jmp there"	 
	
        


gather_info()
print "\n"
while(1):

	print "[ 1 ]  Where to write "
	print "[ 2 ]  What  to write "
	print "[ 3 ]  Exit \n"
	val = raw_input('Action: ')
	if val == '1' :
	   where()
	elif val == '2' :
	   what()
	else :
	
	   print "[*] If u are comletely blind try to use Dynelf from pwntools\n\n "
	   print "[*] Happy pwning :)"	
	   break 






