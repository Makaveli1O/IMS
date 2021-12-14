import numpy as np
import matplotlib.pyplot as plt

# data to be plotted
x = ["Assembly machines", "Clinching tables", "Panel Machines", "Border Machines", "Padding Tables", "Tape Machines", "Packing Machines"]
y =  [274, 0, 0.0649349, 0.168704, 129.95, 0, 0.12629]
 
# plotting
plt.title("Průmněrná čekací doba u jednotlivých linek")
plt.xlabel("X axis")
plt.ylabel("Y axis")
plt.bar(x, y, color ="red")
plt.show()