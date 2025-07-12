import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Load metrics data
metrics = pd.read_csv('data/metrics.csv')
metrics['theta0'] = metrics['theta0'].astype(float)

# Extract analytic period (same for all angles)
analytic_T = metrics.loc[metrics['mode'] == 'analytic', 'period'].iloc[0]

# Plot 1: Period vs theta0 for each mode
plt.figure()
for mode, group in metrics.groupby('mode'):
    plt.plot(group['theta0'], group['period'], marker='o', label=mode)
plt.xlabel('Initial Angle θ₀ (deg)')
plt.ylabel('Estimated Period T (s)')
plt.title('Period vs Initial Angle')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig('output/period_vs_theta0.png')

# Plot 2: Absolute period error vs theta0 (exclude analytic)
plt.figure()
for mode, group in metrics[metrics['mode'] != 'analytic'].groupby('mode'):
    plt.plot(group['theta0'], group['max_error'], marker='o', label=mode)
plt.xlabel('Initial Angle θ₀ (deg)')
plt.ylabel('Absolute Period Error |T_num - T_lin| (s)')
plt.title('Period Error vs Initial Angle')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig('output/error_vs_theta0.png')

# Plot 3: Steps vs theta0 for each non-analytic mode
plt.figure()
for mode, group in metrics[metrics['mode'] != 'analytic'].groupby('mode'):
    plt.plot(group['theta0'], group['steps'], marker='o', label=mode)
plt.xlabel('Initial Angle θ₀ (deg)')
plt.ylabel('Number of Steps')
plt.title('Step Count vs Initial Angle')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig('output/steps_vs_theta0.png')

plt.figure()
for mode, group in metrics[metrics['mode'] == 'adaptive'].groupby('mode'):
    plt.plot(group['theta0'], group['steps'], marker='o', label=mode)
plt.xlabel('Initial Angle θ₀ (deg)')
plt.ylabel('Number of Steps')
plt.title('Step adaptive vs Initial Angle')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig('output/steps_a_vs_theta0.png')

# Plot 4: CPU time vs theta0 for each non-analytic mode
plt.figure()
for mode, group in metrics[metrics['mode'] != 'analytic'].groupby('mode'):
    plt.plot(group['theta0'], group['cpu_time'], marker='o', label=mode)
plt.xlabel('Initial Angle θ₀ (deg)')
plt.ylabel('CPU Time (s)')
plt.title('CPU Time vs Initial Angle')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig('output/cpu_time_vs_theta0.png')

# Plot 5: Real-time capability summary
real_time_summary = metrics.groupby('mode')['real_time'].apply(lambda s: (s == 'yes').mean())
plt.figure()
real_time_summary.plot(kind='bar')
plt.xlabel('Mode')
plt.ylabel('Proportion of Real-Time Steps')
plt.title('Real-Time Capability by Mode')
plt.tight_layout()
plt.savefig('output/real_time_summary.png')

coisa_theta = 0
coisa_error = 0
for idx, row in metrics.iterrows():
    if row['max_error'] > 0.001:
        break
    
    coisa_theta = row['theta0']
    coisa_error = row['max_error']


error_threshold = f"Maximum error threshold exceeded at θ₀={coisa_theta}° with error {coisa_error}s"
with open('output/error_threshold.txt', 'w', encoding='utf-8') as f:
    f.write(error_threshold)
    
print("Plots generated in output/ folder:")
print("- period_vs_theta0.png")
print("- error_vs_theta0.png")
print("- steps_vs_theta0.png")
print("- cpu_time_vs_theta0.png")
print("- real_time_summary.png")
print("- real_time_summary.png")
print("Error threshold information saved to error_threshold.txt")