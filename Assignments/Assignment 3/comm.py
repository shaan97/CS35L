#!/usr/bin/python

import sys
from optparse import OptionParser

class Set:
    def __init__(self, words):
        self.items = {}
        for word in words:
            self.items[word] = 0

    def exists(self, word):
        try:
            self.items[word] += 1
            del self.items[word]
            return True
        except:
            return False
        






def print_comm(list1, list2, options):
    i = j = 0
    tab2 = "\t"
    tab3 = "\t\t"
    if options.one:
        if options.two:
            tab3 = ""
        else:
            tab2 = ""
            tab3 = "\t"
    else:
        if options.two:
            tab3 = "\t"
    
    while i != len(list1) and  j != len(list2):
        if list1[i] < list2[j]:
            if not options.one:
                sys.stdout.write(list1[i] + "\n")
            i = i + 1
        elif list1[i] > list2[j]:
            if not options.two:
                sys.stdout.write(tab2 + list2[j] + "\n")
            j = j + 1
        else:
            if not options.three:
                sys.stdout.write(tab3 + list1[i] + "\n")
            i = i + 1
            j = j + 1

    # i == len(list1) or j == len(list2)

    if i == len(list1):
        list3 = list2
        k = j
        tab = tab2
        shouldNotPrint = options.two
    else:
        list3 = list1
        k = i
        tab = ""
        shouldNotPrint = options.one

    while k != len(list3):
        if not shouldNotPrint:
            sys.stdout.write(tab + list3[k] + "\n")
        k = k + 1


def print_u_comm(list1, set2, options, list2):
    tab2 = "\t"
    tab3 = "\t\t"
    if options.one:
        if options.two:
            tab3 = ""
        else:
            tab2 = ""
            tab3 = "\t"
    else:
        if options.two:
            tab3 = "\t"
    


    for word in list1:
        if set2.exists(word):
            if not options.three:
                sys.stdout.write(tab3 + word + "\n")
        else:
            if not options.one:
                sys.stdout.write(word + "\n")


    for key in list2:
        if key in set2.items and not options.two:
            sys.stdout.write(tab2 + key + "\n")


def main():
    version_msg = "%prog 2.0"
    usage_msg = "%prog [-123u] FILE1 FILE2"
    
    parser = OptionParser(version=version_msg, usage=usage_msg)
    parser.add_option("-1", action="store_true", dest="one", default=0)
    parser.add_option("-2", action="store_true", dest="two", default=0)
    parser.add_option("-3", action="store_true", dest="three", default=0)
    parser.add_option("-u", action="store_true", dest="unordered", default=0)

    options, args = parser.parse_args(sys.argv[1:])

    if len(args) != 2:
        parser.error("Wrong number of arguments.")
    
    file1 = args[0];
    file2 = args[1];
    lines1 = []
    lines2 = []
    
    if file1 == "-" and file2 == "-":
        parser.error("Both files cannot be from STDIN")

    if file1 == "-":
        lines1 = sys.stdin.readlines()

        try:
            f = open(file2, 'r')
            lines2 = f.readlines()
            f.close()
        except:
            parser.error("Invalid FILE2")
    elif file2 == "-":
        lines2 = sys.stdin.readlines()

        try:
            f = open(file1, 'r')
            lines1 = f.readlines()
            f.close()
        except:
            parser.error("Invalid FILE1")
    else:
        try:
            f = open(file1, 'r')
            lines1 = f.readlines()
            f.close()
        except:
            parser.error("Invalid FILE1")

        try:
            f = open(file2, 'r')
            lines2 = f.readlines()
            f.close()
        except:
            parser.error("Invalid FILE2")

    # Test code
    """
    for line in lines1:
        print(line)
    for line in lines2:
        print(line)
    """

    """
    if options.one:
        print("Option one detected")
    if options.two:
        print("Option two detected")
    if options.three:
        print("Option three detected")
    """
    
    lines1 = [i.replace('\n', '') for i in lines1]
    lines2 = [i.replace('\n', '') for i in lines2]

    if options.unordered:
        set2 = Set(lines2)
        print_u_comm(lines1, set2, options, lines2)
    else:
        print_comm(lines1, lines2, options)

    
    
if __name__ == "__main__":
    main()


          
"""
list_1 = ["D", "B", "A", "C"]
list_2 = ["A", "F", "C", "E"]
set2 = Set(list_2)

print_u_comm(list_1, set2)

"""
"""
list1 = ["car", "car", "mirror"]
list2 = ["car", "door", "tires"]
print_comm(list1, list2)
"""
"""
test1 = ["car", "mirror", "car", "beer"]
test2 = ["tires", "door", "mirror", "car", "apple"]

set_test2 = Set(test2)
print_u_comm(test1, set_test2)
"""
