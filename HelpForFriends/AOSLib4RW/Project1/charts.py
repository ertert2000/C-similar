import matplotlib.pyplot as plt
import pandas as pd
import re
from matplotlib.patches import Patch
from collections import defaultdict
import glob
import os

def parse_log(path, role):
    pid = os.path.splitext(os.path.basename(path))[0].split("_")[1]
    with open(path, encoding='utf-8') as f:
        lines = f.readlines()

    events = []
    current = {}
    for line in lines:
        line = line.strip()
        if line.startswith('[WAITING]'):
            current = {'role': role, 'pid': pid, 'start': int(re.search(r'\d+', line).group()), 'state': 'WAITING'}
        elif '[READING]' in line or '[WRITING]' in line:
            current['action'] = 'READING' if 'READING' in line else 'WRITING'
            current['page'] = int(re.search(r'Page (\d+)', line).group(1))
            current['action_time'] = int(re.search(r'at (\d+)', line).group(1))
        elif '[RELEASE]' in line:
            current['end'] = int(re.search(r'\d+', line).group())
            events.append(current.copy())

    return pd.DataFrame(events)

all_logs = []

for file in glob.glob("reader_*.log"):
    all_logs.append(parse_log(file, "reader"))

for file in glob.glob("writer_*.log"):
    all_logs.append(parse_log(file, "writer"))

df = pd.concat(all_logs).sort_values(by='start').reset_index(drop=True)

def plot_timeline(df):
    fig, ax = plt.subplots(figsize=(14, len(df['pid'].unique()) * 0.5))
    colors = {'WAITING': 'gray', 'READING': 'skyblue', 'WRITING': 'salmon'}
    y_labels = []
    y = 0

    for pid in df['pid'].unique():
        proc_df = df[df['pid'] == pid]
        for _, row in proc_df.iterrows():
            ax.barh(y, row['action_time'] - row['start'], left=row['start'], color=colors['WAITING'])
            ax.barh(y, row['end'] - row['action_time'], left=row['action_time'], color=colors[row['action']])
        y_labels.append(f"{row['role']}_{pid}")
        y += 1

    ax.set_yticks(range(len(y_labels)))
    ax.set_yticklabels(y_labels)
    ax.set_xlabel("Время (мс)")
    ax.set_title("Смена состояний процессов")
    ax.legend(handles=[
        Patch(facecolor='gray', label='Ожидание'),
        Patch(facecolor='skyblue', label='Чтение'),
        Patch(facecolor='salmon', label='Запись')
    ])
    plt.tight_layout()
    plt.savefig("timeline.png", dpi=300)
    plt.show()

plot_timeline(df)

heatmap = defaultdict(list)
for _, row in df.iterrows():
    for t in range(row['action_time'], row['end'], 100):
        heatmap[row['page']].append((t, row['role']))

times = sorted(set(t for entries in heatmap.values() for t, _ in entries))
pages = sorted(heatmap.keys())
matrix = pd.DataFrame(index=pages, columns=times)

for page in pages:
    for t, who in heatmap[page]:
        matrix.loc[page, t] = 1 if who == 'writer' else 0.5

plt.figure(figsize=(15, 6))
plt.imshow(matrix.fillna(0), aspect='auto', cmap='coolwarm', interpolation='nearest')
plt.colorbar(label='0.5 = Чтение, 1 = Запись')
plt.title("Занятость страниц по времени (heatmap)")
plt.ylabel("Номер страницы")
plt.xlabel("Момент времени (шаг 100 мс)")
plt.tight_layout()
plt.savefig("heatmap.png", dpi=300)
plt.show()
