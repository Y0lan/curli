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
curli
# a configuration file will be created to $HOME/.config/curli/conf.sconf
# the help will be displayed
# next : put a template inside the configuration file
# next : read the configuration file and save each task into struct
```