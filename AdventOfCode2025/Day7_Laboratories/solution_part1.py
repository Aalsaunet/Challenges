split_count = 0
f = open("input.txt", "r")
prev_row = {f.readline().find("S")}
line = f.readline()
while line:
    curr_row = set()
    for _, j in enumerate(prev_row):
        if (line[j] == "^"):
            curr_row.add(j - 1)
            curr_row.add(j + 1)
            split_count += 1
        else :
           curr_row.add(j) 
    prev_row = curr_row
    line = f.readline()    

f.close()
print(split_count)
