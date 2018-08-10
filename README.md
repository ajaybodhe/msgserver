# msgserver
C code to send messages to upstream servers

#compile code
make clean
make

#test code
cd test
python server.py
cd ..
sendmsg -s 127.0.0.1 -p 5555 -m "hello server"