with open("input.txt", "r") as f:
    grid = f.read().splitlines()
start_col = grid[0].find("S")
active_timelines = {start_col: 1}

for row in range(1, len(grid)):
    next_timelines = {}
    for col, count in active_timelines.items():
        char = grid[row][col] if col < len(grid[row]) else '.'
        if char == '^':
            next_timelines[col - 1] = next_timelines.get(col - 1, 0) + count
            next_timelines[col + 1] = next_timelines.get(col + 1, 0) + count
        else:
            next_timelines[col] = next_timelines.get(col, 0) + count 
    active_timelines = next_timelines

print(f"Timelines: {sum(active_timelines.values())}")
