#!/usr/bin/env python3

from ViennaExample import HelloWorld

hw = HelloWorld()

assert hw.prefix == ""

hw.prefix = "myMessage"
assert hw.prefix == "myMessage"
