# -*- coding: utf-8 -*-
"""
Created on Sun Oct 31 22:14:32 2021

@author: Steve D. J.
"""

import pandas as pd

og_data = pd.read_excel('PathData.xlsx', index_col = None, header = None)
f = open('PathDataN.txt', 'w')

for i in range(0, 128):
    for j in range(i + 1, 128):
        og_data.iloc[j, i] = og_data.iloc[i, j]

for i in range(0, 128):
    t_str = ""
    for j in og_data.iloc[i, :].values:
        if j == 0 or j == 1:
            f.write(str(int(j)))
    f.write('\n')
        
f.close()