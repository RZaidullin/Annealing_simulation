import csv
import random
proc_num = [400] # random.randint(1, 5)
work_num = [4000] # random.randint(1, 20)
work_times = [random.randint(1, 100) for i in range(work_num[0])]
procs = [5, 10, 20, 50, 100, 200, 300, 400]
works = [500, 700, 1000, 1200, 1600, 2000, 2500, 3000, 3500, 4000]
with open('example.csv', 'w', newline='', encoding='utf-8') as file:
    for i in range(len(procs)):
        for j in range(len(works)):
            work_times = [random.randint(1, 100) for p in range(works[j])]
            writer = csv.writer(file)
            writer.writerow([procs[i]])
            writer.writerow([works[j]])
            writer.writerow(work_times)