#!/usr/bin/env python3

from ViennaExample import HelloWorld

# test construction
hw = HelloWorld()

# print "Hello, World!"
hw.print()

# print our own text
hw.print("This is an example!")

# set new prefix for output
hw.prefix = "Output: "

# test output with prefix
hw.print()
