package momfo.problems.singletask;

import jmetal.core.Problem;
import jmetal.core.Solution;
import jmetal.core.Variable;
import jmetal.encodings.solutionType.BinaryRealSolutionType;
import jmetal.encodings.solutionType.RealSolutionType;
import jmetal.util.JMException;
import momfo.problems.core.GFunctions;

public class NIHS1 extends Problem {
	public NIHS1(String solutionType) {
		numberOfVariables_ = 50;
		numberOfObjectives_ = 2;
		numberOfConstraints_ = 0;
		problemName_ = "NIHS1";

		lowerLimit_ = new double[numberOfVariables_];
		upperLimit_ = new double[numberOfVariables_];
		
		
		lowerLimit_[0] = 0;
		upperLimit_[0] = 1;
		
		for (int i = 1; i < numberOfVariables_; i++) {
			lowerLimit_[i] = -80;
			upperLimit_[i] = 80;
		}


		if (solutionType.compareTo("BinaryReal") == 0)
			solutionType_ = new BinaryRealSolutionType(this);
		else if (solutionType.compareTo("Real") == 0)
			solutionType_ = new RealSolutionType(this);
		else {
			System.out.println("Error: solution type " + solutionType + " invalid");
			System.exit(-1);
		}
	} // NIHS1
	
	
	@Override
	public void evaluate(Solution solution) throws JMException {
		Variable[] decisionVariables = solution.getDecisionVariables();

		double[] f = new double[numberOfObjectives_]; 
		double[] x = new double[numberOfVariables_]; 

		for (int i = 0; i < numberOfVariables_; i++)
			x[i] = decisionVariables[i].getValue();

		double q = GFunctions.getRosenbrock(x, 1, numberOfVariables_ - 1);
		
		f[0] = q * Math.cos(0.5 * Math.PI * x[0]);
		f[1] = q * Math.sin(0.5 * Math.PI * x[0]);
		
		solution.setObjective(0, f[0]);
		solution.setObjective(1, f[1]);
	}

}
