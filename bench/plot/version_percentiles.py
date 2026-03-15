import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import glob
import re
import os

def format_latency(y, pos):
    """ Converts seconds to human-readable units. """
    if y >= 1: return f'{y:.2f} s'
    if y >= 1e-3: return f'{y*1e3:.2f} ms'
    if y >= 1e-6: return f'{y*1e6:.2f} us'
    return f'{y*1e9:.2f} ns'

def parse_benchmark_filename(filepath):
    """
    Parses {date}-{name}-{version}.csv
    Example: 2026-03-14-1M_rand_fill-trie_v1.csv
    Returns: (test_name, version_tag)
    """
    filename = os.path.basename(filepath)
    # Regex splits by hyphen, but we want to capture the version part specifically
    # This logic assumes: YYYY-MM-DD-NAME-VERSION.csv
    match = re.search(r"\d{4}-\d{2}-\d{2}-(.+)-(.+)\.csv$", filename)
    if match:
        return match.group(1), match.group(2)
    return filename, "unknown"

# 1. Data Collection
arquivos = glob.glob("bench/results/*.csv")
data_frames = []

percentis = [
    '50th_percentile', '90th_percentile', '99th_percentile', 
    '99.9th_percentile', '99.99th_percentile', '99.999th_percentile'
]
clean_labels = ['P50', 'P90', 'P99', 'P99.9', 'P99.99', 'P99.999']

for f in arquivos:
    test_name, version_tag = parse_benchmark_filename(f)
    try:
        df = pd.read_csv(f)
        df.columns = df.columns.str.strip()
        
        # Take the first row and rename columns for the plot
        row = df.iloc[0][percentis].to_frame().T
        row.columns = clean_labels
        row['version'] = version_tag
        row['test_name'] = test_name
        data_frames.append(row)
    except Exception as e:
        print(f"Error processing {f}: {e}")

if not data_frames:
    print("No CSV files found in bench/results/")
    exit()

full_df = pd.concat(data_frames, ignore_index=True)

# 2. Plotting (Grouping by version)
plt.style.use('seaborn-v0_8-muted')
fig, ax = plt.subplots(figsize=(14, 8))

# Pivot so 'version' becomes the legend/columns
plot_data = full_df.set_index('version')[clean_labels].T
plot_data.plot(kind='bar', ax=ax, width=0.8, edgecolor='black', linewidth=0.5)

# Styling
ax.set_yscale('log')
ax.yaxis.set_major_formatter(ticker.FuncFormatter(format_latency))
ax.set_title('Tail Latency Comparison: Distribution Breakdown', fontsize=16, fontweight='bold', pad=25)
ax.set_ylabel('Latency (Log Scale)', fontsize=12, labelpad=10)
ax.set_xlabel('Percentile', fontsize=12)
ax.grid(True, which="both", axis='y', ls="--", alpha=0.3)
plt.xticks(rotation=0)

# Value Labels
for p in ax.patches:
    h = p.get_height()
    if h > 0:
        ax.annotate(format_latency(h, None), 
                    (p.get_x() + p.get_width() / 2., h),
                    ha='center', va='bottom', xytext=(0, 5),
                    textcoords='offset points', fontsize=8, fontweight='bold', rotation=45)

plt.legend(title="Implementation / Version", frameon=True, loc='upper left', bbox_to_anchor=(1, 1))
plt.tight_layout()

# Save with a clean name
plt.savefig('bench/results/latency_comparison_v2.png', dpi=300, bbox_inches='tight')
plt.show()