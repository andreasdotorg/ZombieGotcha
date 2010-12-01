Howdy y'all,

Each sprite will be referenced by name in C code, as there aren't
enough to justify any strange database.  In general, these won't be
sent over the network, but rather loaded locally.

In this directory, for every sprite, there should be both a BMP (of
any color depth, though 1-bit B&W is our de facto standard) and--more
importantly--an ASCII-formatted PNM for use by the conversion tool.

Sprites are held in Flash, rather than Ram, but it is still wise to
conserve memory wherever possible.  Plan on 1 bit per pixel, and always
keep the width and height as even multiples of 8 pixels.

--Travis

