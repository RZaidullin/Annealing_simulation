#%%
#imports
import pandas as pd
import numpy as np

import matplotlib.pyplot as plt
import seaborn as sns

from datetime import datetime

# Boltzmann

procs = [5, 10, 20, 50, 100, 200, 300, 400]
works = [500, 700, 1000, 1200, 1600, 2000, 2500, 3000, 3500, 4000]

start_criterion = []
final_criterion = []
times = []

with open('data2.txt', 'r', newline='', encoding='utf-8') as file:
    # for i in range(len(procs)):
    #     for j in range(len(works)):
    #         s = file.read()
    #         print(s[0], s[1])
    #         break
    #     break
    cnt = 0
    tmp_start = []
    tmp_final = []
    tmp_times = []

    for line in file:
        word = line.split()
        if cnt < 10:
            tmp_start.append(int(word[2]))
            tmp_final.append(int(word[5]))
            tmp_times.append(float(word[6][9:]))
        else:
            cnt = 0
            start_criterion.append(tmp_start)
            final_criterion.append(tmp_final)
            times.append(tmp_times)
            tmp_start = []
            tmp_final = []
            tmp_times = []
            tmp_start.append(int(word[2]))
            tmp_final.append(int(word[5]))
            tmp_times.append(float(word[6][9:]))
        cnt += 1
        # print(word[2], word[5], word[6][9:])
        # break
    start_criterion.append(tmp_start)
    final_criterion.append(tmp_final)
    times.append(tmp_times)
# print(start_criterion, len(start_criterion))
# print(final_criterion, len(final_criterion))
# print(times, len(times))

# lang = ['deu', 'eng', 'fra', 'ita', 'por', 'spa']
# # procs.append(1)
# works.append(1)
conf_matrix_df = pd.DataFrame(times,columns=works,index=procs)

plt.figure(figsize=(10, 10))
sns.set(font_scale=1.0)

sns.heatmap(conf_matrix_df,
            # cmap='coolwarm',
            annot=True,
            fmt='.5g',
            vmax=70)

plt.xlabel('Works',fontsize=22)
plt.ylabel('Processors',fontsize=22)

# print(1)
# %%
