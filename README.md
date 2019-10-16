# curli
Curl, improved.
Working only for GNU/Linux
# For us, developpers
```bash
aclocal # Set up an m4 environment
autoconf # Generate configure from configure.ac
automake --add-missing # Generate Makefile.in from Makefile.am
./configure # Generate Makefile from Makefile.in
make distcheck # Use Makefile to build and test a tarball to distribute
```

# Install it
```bash
./configure # Generate Makefile from Makefile.in
make # Use Makefile to build the program
make install # Use Makefile to install the program²
```

# Test it (will change while curli gets more feature)
```bash
curli # Wed Oct 16 17:21:11 2019
```