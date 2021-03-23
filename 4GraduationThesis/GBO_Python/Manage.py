import numpy as np
from BenchmarkFunctions import BenchmarkFunctions
from Optimizer.GBO import GBO
from Optimizer.GA import GA
from Optimizer.DE import DE
from Optimizer.PSO import PSO
from Draw import Draw


class Manage:
    def __init__(self, nP, nV, MaxIt, testNum):
        self.nP = nP
        self.MaxIt = MaxIt
        self.testNum = testNum
        self.bmf = BenchmarkFunctions(D=nV)

    def runGBO(self, fname):
        print("GBO")
        lb, ub, nV, fobj = self.bmf.get(fname)
        np_best_cost = np.empty([self.testNum])
        np_best_x = np.empty([self.testNum, nV])
        np_convergence_curve = np.empty([self.testNum, self.MaxIt])

        for i in range(self.testNum):
            gbo = GBO(self.nP, self.MaxIt, lb, ub, nV, fobj)
            np_best_cost[i], np_best_x[i], np_convergence_curve[i] = gbo.run()
            print("%d test: " % (i + 1), np_best_cost[i])

        best_cost = np_best_cost.min()
        ave_cost = np_best_cost.mean()
        var_cost = np_best_cost.var()
        ave_convergence_curve = np.empty((self.MaxIt))
        for i in range(self.MaxIt):
            ave_convergence_curve[i] = np_convergence_curve[:, i].mean()
        return best_cost, ave_cost, var_cost, ave_convergence_curve

    def runGA(self, fname):
        print("GA")
        lb, ub, nV, fobj = self.bmf.get(fname)
        np_best_cost = np.empty([self.testNum])
        np_best_x = np.empty([self.testNum, nV])
        np_convergence_curve = np.empty([self.testNum, self.MaxIt])

        for i in range(self.testNum):
            ga = GA(nP=self.nP, MaxIt=self.MaxIt,
                    lb=lb, ub=ub, nV=nV, fobj=fobj)
            np_best_cost[i], np_best_x[i], np_convergence_curve[i] = ga.run()
            print("%d test: " % (i + 1), np_best_cost[i])

        best_cost = np_best_cost.min()
        ave_cost = np_best_cost.mean()
        var_cost = np_best_cost.var()
        ave_convergence_curve = np.empty((self.MaxIt))
        for i in range(self.MaxIt):
            ave_convergence_curve[i] = np_convergence_curve[:, i].mean()
        return best_cost, ave_cost, var_cost, ave_convergence_curve

    def runDE(self, fname):
        print("DE")
        lb, ub, nV, fobj = self.bmf.get(fname)
        np_best_cost = np.empty([self.testNum])
        np_best_x = np.empty([self.testNum, nV])
        np_convergence_curve = np.empty([self.testNum, self.MaxIt])

        for i in range(self.testNum):
            de = DE(nP=self.nP, MaxIt=self.MaxIt,
                    lb=lb, ub=ub, nV=nV, fobj=fobj)
            np_best_cost[i], np_best_x[i], np_convergence_curve[i] = de.run()
            print("%d test: " % (i + 1), np_best_cost[i])

        best_cost = np_best_cost.min()
        ave_cost = np_best_cost.mean()
        var_cost = np_best_cost.var()
        ave_convergence_curve = np.empty((self.MaxIt))
        for i in range(self.MaxIt):
            ave_convergence_curve[i] = np_convergence_curve[:, i].mean()
        return best_cost, ave_cost, var_cost, ave_convergence_curve

    def runPSO(self, fname):
        print("PSO")
        lb, ub, nV, fobj = self.bmf.get(fname)
        np_best_cost = np.empty([self.testNum])
        np_best_x = np.empty([self.testNum, nV])
        np_convergence_curve = np.empty([self.testNum, self.MaxIt])

        for i in range(self.testNum):
            pso = PSO(nP=self.nP, MaxIt=self.MaxIt,
                      lb=lb, ub=ub, nV=nV, fobj=fobj)
            np_best_cost[i], np_best_x[i], np_convergence_curve[i] = pso.run()
            print("%d test: " % (i + 1), np_best_cost[i])

        best_cost = np_best_cost.min()
        ave_cost = np_best_cost.mean()
        var_cost = np_best_cost.var()
        ave_convergence_curve = np.empty((self.MaxIt))
        for i in range(self.MaxIt):
            ave_convergence_curve[i] = np_convergence_curve[:, i].mean()
        return best_cost, ave_cost, var_cost, ave_convergence_curve


if __name__ == "__main__":
    mng = Manage(nP=50, nV=20, MaxIt=500, testNum=10)
    for fname in range(1, mng.bmf.size+1):
        lb, ub, nV, fobj = mng.bmf.get(fname)
        # draw = Draw(isShow=True)
        # draw.drawFunction3D(lb, ub, fobj)

        print()
        print(fobj.__doc__)
        cost_gbo, ave_gbo, var_gbo, cc_gbo = mng.runGBO(fname)
        cost_ga, ave_ga, var_ga, cc_ga = mng.runGA(fname)
        cost_de, ave_de, var_de, cc_de = mng.runDE(fname)
        cost_pso, ave_pso, var_pso, cc_pso = mng.runPSO(fname)

        print("- Best Cost -")
        print("GBO: ", cost_gbo)
        print("GA : ", cost_ga)
        print("DE : ", cost_de)
        print("PSO: ", cost_pso)
        print()
        print("- Average Cost -")
        print("GBO: ", ave_gbo)
        print("GA : ", ave_ga)
        print("DE : ", ave_de)
        print("PSO: ", ave_pso)
        print()
        print("- Variance Cost -")
        print("GBO: ", var_gbo)
        print("GA : ", var_ga)
        print("DE : ", var_de)
        print("PSO: ", var_pso)

        # y轴最大值
        y1 = np.array([cc_gbo[0], cc_ga[0], cc_de[0], cc_pso[0]])
        idx = np.argsort(y1)
        y_lim = y1[idx[0:1]].mean()

        lim = range(0, mng.MaxIt)
        draw = Draw(isShow=False, isSavefig=True)
        draw.drawPloterro([cc_gbo[lim], cc_ga[lim], cc_de[lim], cc_pso[lim]],
                          ['GBO', 'GA', 'DE', 'PSO'],
                          fobj.__doc__,
                          y_lim)
