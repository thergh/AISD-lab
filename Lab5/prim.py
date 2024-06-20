import matplotlib.pyplot as plt

# Data
n_values = [1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000]
prim = [1998000, 7996000, 17994000, 31992000, 49990000, 71988000, 97986000, 127984000, 161982000, 199980000]
kruskal = [1002000, 4004000, 9006000, 16008000, 25010000, 36036000, 49049000, 64064000, 81081000, 100100000]

# Plot
plt.figure(figsize=(10, 6))
plt.plot(n_values, prim,  label="Prim's")
plt.plot(n_values, kruskal, label="Kruskal's")

# Labels and Title
plt.xlabel('Number of Vertices (n)')
plt.ylabel('Number of Comparisons')
plt.title("Number of Comparisons in Prim's and Kruskal's Algorithms")
plt.grid(True)
plt.legend()

# Show plot
plt.savefig("comps.png")
plt.show()
