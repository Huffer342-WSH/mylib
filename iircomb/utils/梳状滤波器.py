# %%
from scipy import signal, io, fft
import matplotlib.pyplot as plt
import numpy as np


def draw_freqz(w, h):
    response = abs(h)
    # To avoid divide by zero when graphing
    response[response == 0] = 1e-20
    # Plot
    fig, ax = plt.subplots(2, 1, figsize=(8, 6), sharex=True)
    ax[0].plot(w, 20 * np.log10(abs(response)), color="blue")
    ax[0].set_title("Frequency Response")
    ax[0].set_ylabel("Amplitude (dB)", color="blue")
    ax[0].grid(True)
    ax[0].set_ylim([-30, 5])

    ax[1].plot(w, (np.angle(h) * 180 / np.pi + 180) % 360 - 180, color="green")
    ax[1].set_ylabel("Angle (degrees)", color="green")
    ax[1].set_xlabel("Frequency (Hz)")
    ax[1].set_yticks([-90, -60, -30, 0, 30, 60, 90])
    ax[1].set_ylim([-90, 90])
    ax[1].grid(True)
    plt.show()


# %%
shift = 27
fs = 1500.0  # Sample frequency (Hz)
f0 = 50.0  # Frequency to be removed from signal (Hz)
Q = 5  # Quality factor
# Design notching comb filter
b, a = signal.iircomb(f0, Q, ftype="notch", fs=fs, pass_zero=False)
print(f"滤波器阶数{len(b)}")
print(f"滤波器系数: b0={b[0]} bn={b[-1]} a0={a[0]} an={a[-1]}")


B_Q12 = np.around(b * (2**shift)).astype(np.int32)
A_Q12 = np.around(a * (2**shift)).astype(np.int32)
freq, h = signal.freqz(b, a, fs=fs, worN=1024)
freqQ, hQ = signal.freqz(B_Q12 / (2**shift), A_Q12 / (2**shift), fs=fs, worN=1024)


struct_str = f"""
CombFiliter_t combfilter = {{     
    .a0 = {A_Q12[0]},
	.an = {A_Q12[-1]},
	.b0 = {B_Q12[0]},
	.bn = {B_Q12[-1]},
	.latest = {len(B_Q12)},
	.numStages = {len(B_Q12)-1},
	.earliest = 0,
}};
    """

print(struct_str)

draw_freqz(freq, h)
draw_freqz(freqQ, hQ)


# %%  仿真测试
def generate_signal(fs, f0, duration):
    # 生成时间向量
    t = np.arange(0, duration, 1 / fs)

    # 生成高斯噪声
    s = np.random.normal(0, 0.5, len(t))

    # 生成正弦波信号
    for i in range(1, int(fs / f0 / 2)):
        s = s + np.sin(2 * np.pi * i * f0 * t)
    s = s * (2**12)
    s = s.astype(np.int32)
    return t, s


t, s = generate_signal(fs, f0, 2)
f = np.arange(0, fs, fs / 512)
s2 = signal.lfilter(b, a, s)
s2 = s2.astype(np.int32)

# %% 打印数据
arr_str = f"int32_t test_in[{len(s)}] = {{"
for i in s:
    arr_str = arr_str + str(i) + ","
arr_str = arr_str[:-1] + "};"
print(arr_str)
arr_str = f"int32_t test_out[{len(s2)}] = {{"
for i in s2:
    arr_str = arr_str + str(i) + ","
arr_str = arr_str[:-1] + "};"
print(arr_str)


# %% 绘图
plt.figure(figsize=(10, 6))
plt.plot(t, s)
plt.title("Signal with Gaussian Noise and Harmonics")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.grid(True)
plt.show()
fig, ax = plt.subplots(2, 1, figsize=(8, 6), sharex=True)
ax[0].plot(f, np.abs(fft.fft(s[-512:])))
ax[1].plot(f, np.abs(fft.fft(s2[-512:])))
ax[1].set_ylim(ax[0].get_ylim())
plt.show()
