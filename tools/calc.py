from __future__ import print_function

import sys

try:
    while True:
        path = raw_input()
        path = 'kjprob.o' + path.split('.')[0]

        time_list = []
        with open(path, 'r') as fp:
            for line in fp:
                if 'seconds' in line:
                    t = float(line.split()[-2])
                    time_list.append(t)
        time_list.sort()

        del time_list[0]
        del time_list[0]
        del time_list[0]
        del time_list[0]
        del time_list[0]
        del time_list[-1]
        del time_list[-1]
        del time_list[-1]
        del time_list[-1]
        del time_list[-1]
        
        print(sum(time_list) / len(time_list), end='\t')
except:
    pass
print()
