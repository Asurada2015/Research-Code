import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from mpl_toolkits.axes_grid1.inset_locator import mark_inset


class Draw:
    def __init__(self, isShow=True, isClose=True):
        self.isShow = isShow
        self.isClose = isClose

    def drawPloterro(self, cc_list, name_list, title, isSave=False, figName=None):
        '''绘制迭代-误差图'''
        fig, ax = plt.subplots(1, 1, figsize=(10, 6))
        axins = ax.inset_axes((0.7, 0.2, 0.25, 0.5))  # 局部放大图

        color = ['r', 'y', 'g', 'b']
        for i in range(len(cc_list)):
            cc = cc_list[i]
            x = [i for i in range(len(cc))]
            ax.plot(x, cc, color[i], linewidth=1.5,
                    markersize=5, label=name_list[i])
            axins.plot(x, cc, color[i], linewidth=1.5,
                       markersize=5, label=name_list[i])

        # 主图
        # y轴的显示范围
        y_ = np.array(cc_list)[:, 2]
        ylim = y_[np.argsort(y_)[0:1]].mean()
        # 设置
        ax.set_xlabel('Iter')
        ax.set_ylabel('Best score')
        ax.set_xlim(0, )
        ax.set_ylim(0, ylim)
        ax.legend()
        ax.set_title(title)

        # 局部图
        # X轴的显示范围
        xlim_l = int(0.95 * len(cc))
        xlim_u = len(cc)
        axins.set_xlim(xlim_l, xlim_u)
        # y轴的显示范围
        y_ = np.array(cc_list)[:, xlim_l-1]
        arg_y = np.argsort(y_)
        ylim = y_[arg_y[-1]] * 1.1
        if y_[arg_y[-1]] > y_[arg_y[-2]] * 50:
            ylim = y_[arg_y[-2]] * 1.1
        if y_[arg_y[-2]] > y_[arg_y[-3]] * 50:
            ylim = y_[arg_y[-3]] * 1.1
        _y = np.array(cc_list)[:, xlim_u-1]
        _arg_y = _y.argsort()
        yy = _y[_arg_y[0:2]]
        ylim_l = yy[0] - (yy[1]-yy[0])
        axins.set_ylim(ylim_l, ylim)
        # loc1 loc2: 坐标系的四个角
        # 1 (右上) 2 (左上) 3(左下) 4(右下)
        mark_inset(ax, axins, loc1=3, loc2=1, fc="none", ec='k', lw=1)

        if isSave:
            plt.savefig(figName)
        if self.isShow:
            plt.show()

    def drawPopScatter3D(self, pop_x, lb, ub, fobj):
        '''绘制3D种群分布图(2-dim)'''
        # fobj
        figure = plt.figure()
        axes = Axes3D(figure)
        step = 0.2
        X = np.arange(lb[0], ub[0], step)
        Y = np.arange(lb[1], ub[1], step)
        X, Y = np.meshgrid(X, Y)
        Z = np.zeros(X.shape)
        for i in range(X.shape[0]):
            for j in range(X.shape[1]):
                Z[i, j] = fobj(np.array([X[i, j], Y[i, j]]))
        axes.plot_surface(X, Y, Z, cmap='rainbow', alpha=.3)

        # pop
        z = np.empty(pop_x.shape[0])
        for i in range(pop_x.shape[0]):
            z[i] = fobj(pop_x[i])
        z = z.T
        pop_t = pop_x.T
        x, y = pop_t[0], pop_t[1]
        axes.scatter(x, y, z, c='r', marker='.')

        plt.xlim(lb[0], ub[0])
        plt.ylim(lb[1], ub[1])
        plt.title(fobj.__doc__)

        if self.isShow:
            plt.show()
        else:
            plt.ion()
            plt.pause(0.2)
            plt.close()

    def drawPopScatter2D(self, pop_x, lb, ub, fobj):
        '''绘制2D种群分布图(2-dim)'''
        # fobj
        plt.figure()
        step = 1
        X = np.arange(lb[0], ub[0], step)
        Y = np.arange(lb[1], ub[1], step)
        X, Y = np.meshgrid(X, Y)
        Z = np.zeros(X.shape)
        for i in range(X.shape[0]):
            for j in range(X.shape[1]):
                Z[i, j] = fobj(np.array([X[i, j], Y[i, j]]))
        plt.contourf(X, Y, Z)
        plt.contour(X, Y, Z)

        # pop
        pop_t = pop_x.T
        x, y = pop_t[0], pop_t[1]
        plt.scatter(x, y, c='r', marker='.', zorder=2)

        plt.xlim(lb[0], ub[0])
        plt.ylim(lb[1], ub[1])
        plt.title(fobj.__doc__)

        if self.isClose:
            plt.ion()
            plt.pause(0.2)
            plt.close()
        else:
            plt.show()

    def drawFunction3D(self, lb, ub, fobj):
        '''绘制函数3D图(2-dim)'''
        lb = lb[0]
        ub = ub[0]

        figure = plt.figure()
        axes = Axes3D(figure)
        X = np.arange(lb, ub, 1)
        Y = np.arange(lb, ub, 1)

        X, Y = np.meshgrid(X, Y)
        Z = np.zeros(X.shape)

        for i in range(X.shape[0]):
            for j in range(X.shape[1]):
                Z[i, j] = fobj(np.array([X[i, j], Y[i, j]]))
        axes.plot_surface(X, Y, Z, cmap='rainbow')
        print(fobj.__doc__)

        if self.isShow:
            plt.show()
