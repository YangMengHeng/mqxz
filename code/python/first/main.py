import matplotlib.font_manager
import numpy as np;
import matplotlib as mpl;
import matplotlib.pyplot as plt;


if __name__ == '__main__':
    mpl.rcParams['font.sans-serif'] = ['Fangsong']
    mpl.rcParams['axes.unicode_minus'] = False


    uni = np.random.uniform(0.0, 1.0, 10000)
    # plt.hist(uni, 80, facecolor='g', alpha=0.75)
    # plt.grid(True)
    # plt.show()

    times = 10000
    for index in range(times):
        uni += np.random.uniform(0.0, 1.0, 10000)

    print(len(uni))
    uni /= times
    print(len(uni))
    plt.hist(uni, 80, facecolor='g', alpha=0.75)
    plt.grid(True)
    plt.show()