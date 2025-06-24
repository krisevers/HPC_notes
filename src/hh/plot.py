import pandas as pd

df = pd.read_csv("voltage_trace.dat", delim_whitespace=True, index_col=0)
df.plot(subplots=True)

import matplotlib.pyplot as plt
plt.savefig("voltage_trace.png")