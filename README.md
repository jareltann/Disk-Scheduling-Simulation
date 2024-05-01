# Disk Scheduling Algorithms

In this project, the Shortest Seek Time First (SSTF) and SCAN algorithms were implemented and compared with First Come First Serve (FCFS)

When the project is executed, it either:
- Accepts a comma-delimited list of unique track numbers from the command-line from the user
- Generates and outputs a list of random track numbers at least 50 distinct tracks in length 

For each algorithm, it would:
- Generate and output the ordered sequence of tracks that requests will be serviced
- Output the total number of tracks traversed (Doesn't implement the "Look" functionality for Scan that turns the r/w head around before reaching the edge of the platter)
- Output the longest delay experienced compared to FCFS
- Output the average delay experienced by all tracks compared to FCFS
