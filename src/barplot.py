import matplotlib.pyplot as plt

# Distances (m)
actual_distances = [0.5, 1, 2, 3, 4]

# # measured distance data (hard coded) -70dbm
# measured_data = {
#     0.5: [0.04, 0.04, 0.02, 0.03],
#     1.0: [0.20, 0.22, 0.20, 0.13],
#     2.0: [1.58, 0.63, 2.51, 2.00, 2.51, 2.51],
#     3.0: [1.78, 3.98, 3.98, 3.16, 2.82, 2.51, 3.98],
#     4.0: [3.55, 4.47, 4.47, 3.98, 2.24, 2.00, 2.24],
# }

# # measured distance data (hard coded) -66dbm
# measured_data = {
#     0.5: [0.04, 0.04, 0.02, 0.03],
#     1.0: [0.32, 0.20, 0.35, 0.35],
#     2.0: [1.58,1.58,2.51,2.51,2.00,2.51],
#     3.0: [2.00, 1.78, 2.00, 1.78, 1.78, 1.78],
#     4.0: [3.55, 3.55, 3.98],
# }

# # measured distance data (hard coded) -59dbm
# measured_data = {
#     0.5: [0.79, 0.89, 0.79, 1.00],
#     1.0: [1.12, 0.79, 1.00, 0.97, 0.89],
#     2.0: [2.24, 2.24, 2.24, 2.00],
#     3.0: [2.24, 2.24, 2.2, 2.51],
#     4.0: [5.01, 5.62, 7.08, 7.08, 7.08, 6.31, 3.98],
# }

# measured distance data (hard coded) -55dbm
measured_data = {
    0.5: [0.40, 0.5, 0.45, 0.50],
    1.0: [3.98,3.55,3.16,3.16,2.82,3.16],
    2.0: [4.47, 3.98, 3.98, 3.98, 4.47, 4.47, 4.47, 3.16, 3.98, 3.98, 3.55],
    3.0: [12.59, 14.13, 10.0, 7.08, 7.08, 7.08, 6.31, 11.22, 11.22],
    4.0: [12.59, 15.85, 10.0, 14.13, 14.13, 12.59, 10.0, 10.0, 10.0],
}
# calculate mean and std
mean_measured = []
std_devs = []
for d in actual_distances:
    values = measured_data[d]
    mean = sum(values) / len(values)
    std = (sum((x - mean) ** 2 for x in values) / len(values)) ** 0.5
    mean_measured.append(mean)
    std_devs.append(std)

# Bar plot (measured values)
x = range(len(actual_distances))
width = 0.4

fig, ax = plt.subplots()
ax.bar(
    x,
    mean_measured,
    width,
    yerr=std_devs,
    capsize=5,
    label="Measured Mean",
    color='orange'
)

# y = x (ideal line)
ax.plot(x, actual_distances, color='blue', linestyle='--', marker='o', label='y = x (ideal)')

# plot settings
ax.set_xticks(x)
ax.set_xticklabels([f"{d} m" for d in actual_distances])
ax.set_ylabel("Distance (m)")
ax.set_title("Measured Distance with Error Bars")
ax.legend()

plt.tight_layout()
plt.show()
