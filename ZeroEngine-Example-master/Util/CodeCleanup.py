import codecs
import glob
import sys

for src in glob.glob("../ZeroEngine/*.h") + glob.glob("../ZeroEngine/*.cpp"):
    inp = outp = src
    content = ""
    with codecs.open(inp, "rU", "utf-8") as infile:
        content = infile.read()
    with codecs.open(outp, "w", "utf-8") as output:
        for line in content.splitlines():
            newline = line.rstrip(" \t")
            output.write(newline + "\r\n")

    print("{} Done.".format(src))
