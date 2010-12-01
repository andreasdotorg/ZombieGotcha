#!/bin/zsh

for foo in *.pnm; (./sprite2c.pl <$foo >../src/art/$foo.inc && echo "Rendered art/$foo.inc")
