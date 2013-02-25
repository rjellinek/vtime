#!/usr/bin/env python
import os, sys
import pprint

def main(root, output_dir):
    '''
    Assumes two columns for each run in the root directory.
    Treats them as ordered pair (x,y), and averages all ys, treating
    xs as labels.

    Outputs results to run_avgs in execution directory.
    '''
    avgs = {}
    alldata = ''
    n = 0

    # Compute totals and n
    for fname in os.listdir(root):
        if 'swp' in fname or os.path.isdir(os.path.join(root,fname)):
            continue
        with open(os.path.join(root,fname), 'r') as fp:
            for line in fp.readlines():
                try:
                    # Necessary to do it this way because of 
                    # extra spaces up front.
                    vals = line.split(' ')
                    x, y = vals[-2], vals[-1]
                except:
                    print '**%s**' % line
                    print os.path.join(root,fname)
                    raise

                alldata += '%s %s' % (x,y)
                
                x = int(x)
                y = float(y)
                if not x in avgs:
                    avgs[x] = 0.0
                avgs[x] += y
            n += 1

    for k,v in avgs.iteritems():
        avgs[k] /= n

    # compute average and output data
    keys = avgs.keys()
    keys.sort()
    s = ''
    for k in keys:
        s += '%s %s\n' % (k,avgs[k])
    
    with open(os.path.join(output_dir, 'avg_runs.dat'), 'w', 0) as fp:
        fp.write(s)
    with open(os.path.join(output_dir, 'combined_runs.dat'), 'w', 0) as fp:
        fp.write(alldata)


if __name__ == '__main__':
    if len(sys.argv) < 3:
        print 'usage: %s <results directory> <output directory>'
        sys.exit()

    main(sys.argv[1], sys.argv[2])
