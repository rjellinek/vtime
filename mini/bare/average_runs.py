#!/usr/bin/env python
import os, sys
import pprint

def main(root):
    '''
    Assumes two columns for each run in the root directory.
    Treats them as ordered pair (x,y), and averages all ys, treating
    xs as labels.

    Outputs results to run_avgs in execution directory.
    '''
    res = {}
    n = 0

    # Compute totals and n
    for fname in os.listdir(root):
        if 'swp' in fname:
            continue
        with open(os.path.join(root,fname), 'r') as fp:
            for line in fp.readlines():
                x, y = line.split(' ')
                
                x = int(x)
                y = float(y)
                if not x in res:
                    res[x] = 0.0
                res[x] += y
            n += 1

    for k,v in res.iteritems():
        res[k] /= n

    # compute average and output data
    s = ''
    for k,v in res.iteritems():
        s += '%s %s\n' % (k,v)
    
    with open('./runs_avg', 'w', 0) as fp:
        fp.write(s)


if __name__ == '__main__':
    if len(sys.argv) < 2:
        print 'usage: %s <results directory>'
        sys.exit()

    main(sys.argv[1])
