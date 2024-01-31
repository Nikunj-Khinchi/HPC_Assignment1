import random

# Set the number of vertices in the graph
n = 3000

# Open the file for writing
with open("graph.txt", "w") as file:
    # Write the number of vertices to the file
    file.write(f"{n}\n")

    # Write the graph matrix to the file with random weights
    for i in range(n):
        for j in range(n):
            if i == j:
                file.write("0 ")
            else:
                weight = random.randint(1, 100)
                file.write(f"{weight} ")

        file.write("\n")

print("Graph file generated successfully.")