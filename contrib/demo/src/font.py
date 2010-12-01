#!/usr/bin/env python


import sys, binascii;

if(len(sys.argv)==1):
    print "usage: ./font.py 0x7f 0x08 0x08 0x08 0x7f 0x00 ";
    sys.exit();

bytes=sys.argv;

for row in [1, 2, 4, 8, 0x10, 0x20, 0x40, 0x80]:
    rowtext="";
    for b in bytes:
        char=" ";
        if(b==sys.argv[0]): b="0xdead";
        if int(b,16)&row: char="X";
        if int(b,16)==0xdead: char="";
        rowtext+=char;
    print "|%s|" % rowtext;

Cstr=""
for b in bytes:
    if b!=sys.argv[0]:
       Cstr+="0x%02x, " % int(b,16); 
print Cstr;
