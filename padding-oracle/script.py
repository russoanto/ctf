from pwn import *

BLOCK_SIZE = 16

connection = connect('localhost',1717)
ciphertext = connection.recvuntil(b'?').decode().split('\n')[1]
print(ciphertext)
#test_cipher = b"CCIP{" + b"0"*10 + b"0"*5*16 + b"}"
#print(test_cipher)
#connect.send(hex(test_cipher))
#print(connect.reciveline())

#blocks_number = len(ciphertext)/BLOCK_SIZE
#print(blocks_number)


#connection.close()

